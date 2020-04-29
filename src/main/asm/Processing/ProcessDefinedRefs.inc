


section '.text' code readable writeable executable align 16

;handle reservedword (parsing must categorize these flags)


namespace processing
processDefinedRefs:
namespace processDefinedRefs
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*17);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsingRefsList qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label prevItemNesting qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label unprocessedParamCount qword at rbp-120
	label processItemListAddr qword at rbp-128
	label processItemAddr qword at rbp-136

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

	and rsp, -32
	push rbx 
	push rbp 
	push rdi 
	push rsi
	push rsp 
	push r12 
	push r13 
	push r14 
	push r15
	sub rsp, 8

	sub rsp, 8*8
	call getProcessItemList
	add rsp, 8*8
	mov [processItemListAddr], rax
	

	mov rcx, 0
	mov [prevItem], rcx			; Begin as 0
	mov [item], rcx			; Begin as 0
	mov [prevItemNesting], rcx
	mov [nesting], rcx

	mov rbx, [parsingAddr]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:
	mov rbx, [parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endParsingRefsList


	
	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	mov [item], rax			; Item is REF_DEFINED or sometimes not (replaceLettersList's first ref that holds alloc)




	sub rsp, 8*8
	mov rcx, [item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [unprocessedParamCount], rax
	cmp rax, 0
	jne hasUnprocessedParams		; Process when any params are unprocessed. Should not matter with defined refs, but maybe will with future changes.

	mov rbx, [item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne nextRefItem			; Skip when already processed (not unprocessed)

	hasUnprocessedParams:					; More params (appending) may be needed with further processing


	;definedRefFlags
	;DEFINED_REF_SEPARATOR	DEFINED_REF_REPLACE_LETTERS_LIST	DEFINED_REF_LETTERS	DEFINED_REF_RETRIEVE_FILE	DEFINED_REF_STORE_FILE


	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM


	sub rsp, 8*8
	mov rcx, [processItemListAddr]
	call [resetIndex]
	add rsp, 8*8



	nextProcessItem:
	mov rbx, [processItemListAddr]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItems


	sub rsp, 8*8
	mov rcx, [processItemListAddr]
	call [getNextItem]
	add rsp, 8*8
	mov [processItemAddr], rax

	mov r10, [processItemAddr]
	add r10, ProcessItem.refFlags
	mov rdx, [r10]
	cmp rdx, 100b		; REF_DEFINED		100b			2	; 
	jne nextProcessItem




	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsingAddr]
	mov qword [rsp+4*8], r10
	mov r15, [processItemAddr]
	add r15, ProcessItem.definedRefFlags
	mov r9, [r15]
	mov r15, [processItemAddr]
	add r15, ProcessItem.refBaseFlags
	mov r8, [r15]
	mov r15, [processItemAddr]
	add r15, ProcessItem.minParamCount
	mov rdx, [r15]
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8


	jmp nextProcessItem
	endItems:



	jmp nextRefItem
	endParsingRefsList:

	sub rsp, 8*8
	mov rcx, [processItemListAddr]
	call [resetIndex]
	add rsp, 8*8


	completed:
	mov rax, [nextRef]


	add rsp, 8	
	pop r15 
	pop r14 
	pop r13 
	pop r12 
	pop rsp 
	pop rsi 
	pop rdi 
	pop rbp 
	pop rbx

	mov rsp, rbp
	pop rbp

	retn 0
end namespace


end namespace