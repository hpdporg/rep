

section '.data' data readable writeable align 16



	;struc File{
	;	.text			dq 0		;
	;}
	


	; Used with address offsets
	;virtual at 0
	;	Element Element
	;end virtual

	; ---- Structures
	;element Element


	fileAddr db 'C:\Users\lewis\Desktop\1100111b.txt',0
	fileHandleAddr dq 0
	fileValue db 'A',0
	fileValue2 db 'B',0
	bytesWritten dq 0
	valueSize dq 0
	;newElementMsg db 'New Element',0
	linear.filePathAddr dq 0

section '.text' code readable writeable executable align 16


; linear.defineFilePath
; linear.newFile

allocate:
namespace allocate
allocate.linear:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*3);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label linear.handleAddr qword at rbp-8  
	label linear.size qword at rbp-16
	label linear.heapAddress qword at rbp-24
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [linear.size], rcx

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
	call [GetProcessHeap]
	mov [linear.heapAddress], rax
	add rsp, 8*8
	

	sub rsp, 8*8
	mov r8, [linear.size]	
	mov rdx, 000001000b
	mov rcx, [linear.heapAddress]
	call [ HeapAlloc] 
	mov [linear.handleAddr], rax
	add rsp, 8*8

	mov rax, [linear.handleAddr]


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