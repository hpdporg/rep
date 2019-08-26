

section '.data' data readable writeable

	struc Rep
		label .
		.layouts dq 0
		.text dq 0
	end struc



section '.text' code readable writeable executable ;align 16


rep:
.new:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label rep.new.heapAddress qword at rbp-8  
	label rep.new.handleAllocatedMemory qword at rbp-16
	;virtual at rbp-64
	;	.html HTML
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









	mov rax, [rep.new.handleAllocatedMemory]


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

