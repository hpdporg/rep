


section '.text' code readable writeable executable align 16



namespace processing
processRestoreFile:
namespace processRestoreFile
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label processedCount qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	label record qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	


	mov rcx, [definedRefFlags]
	mov r9, 100000b						; definedRefFlags	DEFINED_REF_RESTORE_FILE
	cmp rcx, r9 
	jne completed				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 0
	jne completed				; This definedRef depends on param registeredRefs being processed, not just the param



	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8




	nextRefItem:						; Ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax



	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [record], rax

	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [record]
	add rbx, Record.builtLocation
	mov [rbx], rax


	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	mov rbx, [nextRef]
	add rbx, Ref.flags
	mov rdx, [rbx]
	mov rcx, 10b					; REF_LIST
	cmp rcx, rdx
	je listLetters

	
	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	jmp storeRefFile
	listLetters:

	mov r8, [nextRef]
	add r8, Ref.valueAlloc
	mov rcx, [r8]
	sub rsp, 8*8
	call [listAsLetters]
	add rsp, 8*8



	storeRefFile:

	sub rsp, 8*8
	mov rdx, rax 
	mov rcx, [record]
	call [restoreLetters]
	add rsp, 8*8



	;jmp nextRefItem
	endItemList:



	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8

	notReady:


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