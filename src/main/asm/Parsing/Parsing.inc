


section '.data' data readable writeable align 16


	struc Parsing
		label .
		.delimiter dq 0		; Delimiter being used between rep items
		.baseRepOffset dq 0	; Indentation offset used in Rep
		.endDelimiter dq 0	; End of an entry delimiter i.e. newline
		.index dq 0 		; Index of what is being parsed
		.endIndex dq 0		; End of what is being parsed
	end struc


	

	; Used with address offsets
	virtual at 0
		Parsing Parsing
	end virtual

	; ---- Structures
	;element Element


	

	

section '.text' code readable writeable executable align 16


parsing:
namespace parsing
parsing.new:
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
	add rcx, Parsing.subRangeEndIndex
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.transformFlags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.containsRangeList
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.subRangeStartIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.subRangeEndIndex
	mov rax, 0
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