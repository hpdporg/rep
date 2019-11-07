


section '.data' data readable writeable align 16


	struc Ref
		label .
		.ref	dq 0		; Identifier: Letters or Numeric
		.flags dq 0		; Flags
		.unprocessed dq 0	; 0 or 1
		.paramCount dq 0	; Defined Refs may have params
		.repIndex dq 0		; Index into rep
		.list dq 0		; Values, Refs list, Params
	end struc


	

	; Used with address offsets
	virtual at 0
		Ref Ref
	end virtual

	; ---- Structures
	;element Element


	;Flags 
	;REF_DEFINED	REF_LIST	REF_VALUE


	

	

section '.text' code readable writeable executable align 16


ref:
namespace ref
ref.new:
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
	add rcx, Ref.list
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [new.handleAllocatedMemory]
	add rbx, Ref.ref
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Ref.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Ref.unprocessed
	mov rax, 1
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Ref.paramCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Ref.repIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Ref.list
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



end namespace