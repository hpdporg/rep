


section '.data' data readable writeable align 16


	struc RefRegistry
		label .
		.list dq 0		; Delimiter being used between rep items
		.definedList dq 0	; List of defined refs 
	end struc


	

	; Used with address offsets
	virtual at 0
		RefRegistry RefRegistry
	end virtual

	; ---- Structures
	;element Element


	

	

section '.text' code readable writeable executable align 16


refRegistry:
namespace refRegistry
refRegistry.new:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label new.heapAddress qword at rbp-8  
	label new.handleAllocatedMemory qword at rbp-16
	;virtual at rbp-64
	;	.list List
	;end virtual	



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



	sub rsp, 8*4
	call [GetProcessHeap]
	mov [new.heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, RefRegistry.definedList
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [new.handleAllocatedMemory]
	add rbx, RefRegistry.list
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, RefRegistry.definedList
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	



	;lea rax, [new.list]
	;lea rcx, [new.list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [new.list]
	;mov rdi, [storage.new.handleAllocatedMemory]

	;rep movsb


	mov rax, [new.handleAllocatedMemory]


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


refRegistry.newLastRegisteredRef:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newLastRegisteredRef.heapAddress qword at rbp-8  
	label newLastRegisteredRef.handleAllocatedMemory qword at rbp-16
	label newLastRegisteredRef.parsing qword at rbp-24 
	label newLastRegisteredRef.matchIndex qword at rbp-32
	label newLastRegisteredRef.matches qword at rbp-40
	label newLastRegisteredRef.refRegistryAddr qword at rbp-48
	label newLastRegisteredRef.newRef qword at rbp-56
	label newLastRegisteredRef.ref qword at rbp-64
	label next.lettersIndex qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newLastRegisteredRef.refRegistryAddr], rcx
	mov [newLastRegisteredRef.ref], rdx	

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


	mov rcx, 0
	;mov [newLastRegisteredRef.lettersIndex], rcx		; Begin as 0

	
	sub rsp, 8*8
	mov rdx, [newLastRegisteredRef.ref]
	mov rbx, [newLastRegisteredRef.refRegistryAddr]
	add rbx, RefRegistry.list
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8





	mov rax, 0;[newLastRegisteredRef.parsedLetters]



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


refRegistry.newLastRegisteredDefinedRef:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newLastRegisteredDefinedRef.heapAddress qword at rbp-8  
	label newLastRegisteredDefinedRef.handleAllocatedMemory qword at rbp-16
	label newLastRegisteredDefinedRef.parsing qword at rbp-24 
	label newLastRegisteredDefinedRef.matchIndex qword at rbp-32
	label newLastRegisteredDefinedRef.matches qword at rbp-40
	label newLastRegisteredDefinedRef.refRegistryAddr qword at rbp-48
	label newLastRegisteredDefinedRef.newRef qword at rbp-56
	label newLastRegisteredDefinedRef.ref qword at rbp-64
	label newLastRegisteredDefinedRef.lettersIndex qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [newLastRegisteredDefinedRef.refRegistryAddr], rcx
	mov [newLastRegisteredDefinedRef.ref], rdx	
	
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


	mov rcx, 0
	;mov [newLastRegisteredDefinedRef.lettersIndex], rcx		; Begin as 0



	sub rsp, 8*8
	mov rdx, [newLastRegisteredDefinedRef.ref]
	mov rbx, [newLastRegisteredDefinedRef.refRegistryAddr]
	add rbx, RefRegistry.definedList
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8





	mov rax, 0;[newLastRegisteredDefinedRef.parsedLetters]



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



; Existing Ref returned when exists, 0 when non-existent, 1 when defined match
refRegistry.getRegisteredRef:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*10);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getRegisteredRef.heapAddress qword at rbp-8  
	label getRegisteredRef.handleAllocatedMemory qword at rbp-16
	label getRegisteredRef.list qword at rbp-24 
	label getRegisteredRef.definedList qword at rbp-32
	label getRegisteredRef.matches qword at rbp-40
	label getRegisteredRef.refRegistryAddr qword at rbp-48
	label getRegisteredRef.nextRef qword at rbp-56
	label getRegisteredRef.ref qword at rbp-64
	label getRegisteredRef.lettersIndex qword at rbp-72
	label getRegisteredRef.repIndex qword at rbp-80
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getRegisteredRef.refRegistryAddr], rcx
	mov [getRegisteredRef.ref], rdx	
	mov [getRegisteredRef.repIndex], r8


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


	mov rcx, 0
	mov [getRegisteredRef.nextRef], rcx		; Begin as 0


	mov rbx, [getRegisteredRef.refRegistryAddr]
	add rbx, RefRegistry.list
	mov r8, [rbx]
	mov [getRegisteredRef.list], r8

	mov rbx, [getRegisteredRef.refRegistryAddr]
	add rbx, RefRegistry.definedList
	mov r8, [rbx]
	mov [getRegisteredRef.definedList], r8
	
	sub rsp, 8*8
	mov rcx, [getRegisteredRef.list]
	call [resetIndex]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [getRegisteredRef.definedList]
	call [resetIndex]
	add rsp, 8*8


	.nextItem:
	mov rbx, [getRegisteredRef.list]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl getRegisteredRef.endList

	sub rsp, 8*8
	mov rcx, [getRegisteredRef.list]
	call [getNextItem]
	add rsp, 8*8
	mov [getRegisteredRef.nextRef], rax

	sub rsp, 8*8
	mov rdx, [getRegisteredRef.ref]
	mov rbx, [getRegisteredRef.nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [lettersSameExact]
	sub rsp, 8*8
	cmp rax, 0
	je getRegisteredRef.nextItem

	jmp getRegisteredRef.end			; Found

	.endList:

	.nextDefinedItem:
	mov rbx, [getRegisteredRef.definedList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl getRegisteredRef.end

	sub rsp, 8*8
	mov rcx, [getRegisteredRef.definedList]
	call [getNextItem]
	add rsp, 8*8
	mov [getRegisteredRef.nextRef], rax

	sub rsp, 8*8
	mov rdx, [getRegisteredRef.ref]
	mov rbx, [getRegisteredRef.nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [lettersSameExact]
	sub rsp, 8*8
	cmp rax, 0
	je getRegisteredRef.nextItem


	mov rbx, [getRegisteredRef.nextRef]
	add rbx, Ref.repIndex
	mov rdx, [rbx]
	mov rcx, [getRegisteredRef.repIndex]
	cmp rcx, rdx
	jne getRegisteredRef.nextItem




	; return ref instead of 1?
	; how are we determining processed versus not?
	mov rax, 1b
	mov [getRegisteredRef.nextRef], rax			; 1 when defined

	




	.end:

	mov rax, [getRegisteredRef.nextRef]



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

;
;


end namespace