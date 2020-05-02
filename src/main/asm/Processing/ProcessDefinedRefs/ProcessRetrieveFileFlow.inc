


section '.text' code readable writeable executable align 16



namespace processing
processRetrieveFileFlow:
namespace processRetrieveFileFlow
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*17);+(8*6)

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
	label flowAddr qword at rbp-136
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
	mov r9, 1000000b						; definedRefFlags	
	cmp rcx, r9 
	jne completed				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 1b						; Second param can be unprocessed. TO-DO: improve.
	jnle completed				; This definedRef depends on param registeredRefs being processed, not just the param



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


	mov rbx, [record]
	add rbx, Record.allocFlags
	mov rcx, 101b
	mov [rbx], rcx

	mov rbx, [record]
	add rbx, Record.jDelimiter
	mov rcx, [newlineLetters]
	mov [rbx], rcx

	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax
	mov rdx, [nextRef]
	mov [flowAddr], rdx

	



	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [record]
	add rbx, Record.iDelimiter
	mov rcx, rax
	mov [rbx], rcx




	mov rdx, [flowAddr]
	mov [nextRef], rdx




	sub rsp, 8*8
	mov rcx, [record]
	call [retrieve]
	add rsp, 8*8





	mov rbx, [record]
	add rbx, Record.allocAddr
	mov rdx, [nextRef]
	add rdx, Ref.flowAlloc
	mov r8, [rbx]
	mov [rdx], r8
	
	mov rdx, [nextRef]
	add rdx, Ref.flags
	mov r9, [rdx]
	bts r9, 4		; REF_FLOW		10000b			4	; 
	mov [rdx], r9





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