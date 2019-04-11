

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

section '.text' code readable writeable executable align 16

storage:
.newFile:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label storage.newFile.handleAddr qword at rbp-8  
	label storage.newFile.fileNameAddr qword at rbp-16
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [storage.newFile.fileNameAddr], rcx

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


	newFile [storage.newFile.fileNameAddr],[storage.newFile.handleAddr]

	mov rax, [storage.newFile.handleAddr]

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


storage.writeFile:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label storage.writeFile.handleAddr qword at rbp-8  
	label storage.writeFile.entry qword at rbp-16
	label storage.writeFile.size qword at rbp-24
	label storage.writeFile.writtenAddr qword at rbp-32
	;virtual at rbp-64
	;	.list List
	;end virtual	

	mov [storage.writeFile.handleAddr], rcx
	mov [storage.writeFile.entry], rdx
	mov [storage.writeFile.size], r8

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

	lea rbx, [storage.writeFile.writtenAddr]
	writeFile [storage.writeFile.handleAddr],[storage.writeFile.entry],[storage.writeFile.size],rbx
	

	mov rax, [storage.writeFile.handleAddr]

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


macro newFile fileNameAddr,handleAddr

	sub rsp, 8*8
	mov qword [rsp+6*8], 0					;hTemplateFile
	mov qword [rsp+5*8], 128 				;dwFlagsandAttributes
	mov qword [rsp+4*8], 000000100b 			;dwCreationDisposition
	mov r9, 0 						;lpSecurityAttributes
	mov r8, 000000010b 					;dwShareMode
	mov rdx, 10100000000000000000000100000101b		;dwDesiredAccess
	mov rcx, fileNameAddr
	call [CreateFile]
	add rsp, 8*8
	mov handleAddr, rax

	mov rcx, handleAddr
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4

end macro

macro writeFile handleAddr,entry,size,writtenAddr

	mov rcx, handleAddr
	sub rsp, 8*4
	call [SetEndOfFile]
	add rsp, 8*4
	

	sub rsp, 8*8
	mov qword [rsp+4*8], 0
	mov r9, writtenAddr
	mov r8, size
	mov rdx, entry
	mov rcx, handleAddr
	call [WriteFile]
	add rsp, 8*8


end macro


macro byteAsNumeric entry

	mov rbx, 111b
	and bl, cl
	add bl, 48
	mov byte [entry], bl

end macro