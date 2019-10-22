
section '.data' data readable writeable

	
	letterTerminator db 0
	pathSepLetters db '\',0
	directoryContentsLetters db '\*',0
	currentDirLetter db '.',0
	containingDirLetters db '..',0
		
section '.text' code readable writeable executable ;align 16



letters:
namespace letters
letters.numAsLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label numAsLetters.debugMsgSize qword at rbp-8 
	label numAsLetters.heapAddress qword at rbp-16
	label numAsLetters.linearAllocationSize qword at rbp-24
	label numAsLetters.num qword at rbp-32
	label numAsLetters.lettersLength qword at rbp-40
	label numAsLetters.numberNegative qword at rbp-48
	label numAsLetters.lettersBufferReverse qword at rbp-56
	label numAsLetters.lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [numAsLetters.num], rcx


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
	mov [numAsLetters.heapAddress], rax
	add rsp, 8*4


	mov rcx, 0
	add rcx, ListItem.next
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, 200			; 200 bytes		
	mov rdx, 000001000b
	mov rcx, [numAsLetters.heapAddress]
	call [ HeapAlloc] 
	mov [numAsLetters.lettersBufferReverse], rax
	add rsp, 8*4

	sub rsp, 8*4
	mov r8, 200			; 200 bytes		
	mov rdx, 000001000b
	mov rcx, [numAsLetters.heapAddress]
	call [ HeapAlloc] 
	mov [numAsLetters.lettersBufferForward], rax
	add rsp, 8*4

	mov rax, 0
	mov [numAsLetters.lettersLength], rax
	mov [numAsLetters.numberNegative], rax

	mov rcx, [numAsLetters.num]


	cmp rcx, rax
	jns numAsLetters.notNegativeNum

	mov [numAsLetters.numberNegative], 1
	mov rcx, [numAsLetters.num]
	neg rcx
	mov [numAsLetters.num], rcx

	numAsLetters.notNegativeNum:


	mov rax, [numAsLetters.num]
	mov rdx, 0
	mov rbx, 10
	
	mov r9, [numAsLetters.lettersBufferReverse]
	mov rdi, r9
	cld


	numAsLetters.divideDigit:


	idiv rbx

	cmp al, 0
	je numAsLetters.terminateNumString

	add [numAsLetters.lettersLength], 1
	
	mov rbx, rax

	add dl, 48
	mov rax, rdx
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, rbx
	mov rdx, 0
	mov rbx, 10
	jmp numAsLetters.divideDigit


	numAsLetters.terminateNumString:
	
	add [numAsLetters.lettersLength], 1

	add dl, 48
	mov rax, rdx
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, 0
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb


	cmp [numAsLetters.numberNegative], 1
	jne numAsLetters.notNegativeLength

	add [numAsLetters.lettersLength], 1

	numAsLetters.notNegativeLength:

	mov rax, [numAsLetters.lettersLength]


	mov r9, [numAsLetters.lettersBufferReverse]
	mov r10, [numAsLetters.lettersBufferForward]
	mov rsi, r9
	mov r8, r10
	add r8, rax
	mov rdi, r8



	mov rax, 0

	numAsLetters.retrieveReverseNumString:

	std
	mov rcx, 1
	db 10101010b	;db 0xaa	;stosb

	mov rax, 0
	mov rcx, 1
	cld

	lodsb
	
	cmp rax, 0
	jne numAsLetters.retrieveReverseNumString


	cmp [numAsLetters.numberNegative], 1
	jne numAsLetters.noSign
	
	mov rax, 0
	mov al, 150
	mov rcx, 1
	std
	db 10101010b	;db 0xaa	;stosb


	numAsLetters.noSign:



	mov rax, [numAsLetters.lettersBufferForward]

	


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




letters.letterLength:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*4);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label letterLength.letters qword at rbp-8 
	label letterLength.lettersLength qword at rbp-16
	label letterLength.linearAllocationSize qword at rbp-24
	label letterLength.num qword at rbp-32
	;label letterLength.lettersLength qword at rbp-40
	;label letterLength.numberNegative qword at rbp-48
	;label letterLength.lettersBufferReverse qword at rbp-56
	;label letterLength.lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [letterLength.letters], rcx



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


	mov rdx, [letterLength.letters]



	mov rax, 0
	mov rcx, 0
	not rcx
	cld
	mov rdi, rdx

	repne scasb

	
	not rcx
	dec rcx
	mov [letterLength.lettersLength], rcx


	mov rax, [letterLength.lettersLength]


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


letters.appendLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label appendLetters.letters qword at rbp-8 
	label appendLetters.lettersLength qword at rbp-16
	label appendLetters.linearAllocationSize qword at rbp-24
	label appendLetters.newLetters qword at rbp-32
	label appendLetters.newLettersLength qword at rbp-40
	label appendLetters.lettersLengthSum qword at rbp-48
	label appendLetters.appendedLetters qword at rbp-56
	;label appendLetters.lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [appendLetters.letters], rcx
	mov [appendLetters.newLetters], rdx


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

	mov rcx, [appendLetters.letters]
	cmp rcx, 0					; Not appending on anything
	jne appendLetters.lettersNotZero

	mov rdx, [appendLetters.newLetters]
	mov [appendLetters.appendedLetters], rdx
	jmp appendLetters.end


	.lettersNotZero:

	
	sub rsp, 8*8
	mov rcx, [appendLetters.letters]	
	call letterLength
	add rsp, 8*8
	mov [appendLetters.lettersLength], rax

	sub rsp, 8*8
	mov rcx, [appendLetters.newLetters]	
	call letterLength
	add rsp, 8*8
	mov [appendLetters.newLettersLength], rax

	mov rax, [appendLetters.lettersLength]
	mov rcx, [appendLetters.newLettersLength]

	add rax, rcx
	mov [appendLetters.lettersLengthSum], rax

	mov rcx, [appendLetters.lettersLengthSum]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [appendLetters.appendedLetters], rax
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;allocate rcx, appendLetters.appendedLetters

	mov rsi, [appendLetters.letters]
	mov rdi, [appendLetters.appendedLetters]
	cld
	mov rcx, [appendLetters.lettersLength]
	rep movsb

	mov rsi, [appendLetters.newLetters]
	mov rdi, [appendLetters.appendedLetters]
	add rdi, [appendLetters.lettersLength]
	cld
	mov rcx, [appendLetters.newLettersLength]
	rep movsb

	mov rsi, letterTerminator
	mov rdi, [appendLetters.appendedLetters]
	add rdi, [appendLetters.lettersLength]
	add rdi, [appendLetters.newLettersLength]
	mov rcx, 1
	cld
	rep movsb

	.end:

	mov rax, [appendLetters.appendedLetters]

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

; Expects StartIndex, EndIndex as next two Items in indicesList
; Will not resetIndex on indicesList in case there are more unrelated Items in List

letters.betweenListsIndices:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label betweenListsIndices.letters qword at rbp-8 
	label betweenListsIndices.lettersLength qword at rbp-16
	label betweenListsIndices.linearAllocationSize qword at rbp-24
	label betweenListsIndices.newLetters qword at rbp-32
	label betweenListsIndices.newLettersLength qword at rbp-40
	label betweenListsIndices.lettersLengthSum qword at rbp-48
	label betweenListsIndices.indicesList qword at rbp-56
	label betweenListsIndices.lettersBetween qword at rbp-64
	label betweenListsIndices.startIndex qword at rbp-72
	label betweenListsIndices.endIndex qword at rbp-80
	label betweenListsIndices.betweenLength qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [betweenListsIndices.letters], rcx
	mov [betweenListsIndices.indicesList], rdx


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
	mov rcx, [betweenListsIndices.letters]	
	call letterLength
	add rsp, 8*8
	mov [betweenListsIndices.lettersLength], rax

	sub rsp, 8*8
	mov rcx, [betweenListsIndices.indicesList]
	call list.getNextItem
	add rsp, 8*8	
	mov [betweenListsIndices.startIndex], rax

	sub rsp, 8*8
	mov rcx, [betweenListsIndices.indicesList]
	call list.getNextItem
	add rsp, 8*8	
	mov [betweenListsIndices.endIndex], rax

	mov r8, [betweenListsIndices.endIndex]
	mov r9, [betweenListsIndices.startIndex]
	sub r8, r9
	add r8, 1b
	mov [betweenListsIndices.betweenLength], r8


	mov rcx, [betweenListsIndices.betweenLength]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [betweenListsIndices.lettersBetween], rax


	mov rsi, [betweenListsIndices.letters]
	mov r9, [betweenListsIndices.startIndex]
	add rsi, r9

	mov rdi, [betweenListsIndices.lettersBetween]
	mov rcx, [betweenListsIndices.betweenLength]
	cld
	rep movsb

	

	mov rsi, letterTerminator
	mov rdi, [betweenListsIndices.lettersBetween]
	add rdi, [betweenListsIndices.betweenLength]
	mov rcx, 1
	cld
	rep movsb



	mov rax, [betweenListsIndices.lettersBetween]

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

; Expects StartIndex, EndIndex as params


letters.betweenIndices:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label betweenIndices.letters qword at rbp-8 
	label betweenIndices.lettersLength qword at rbp-16
	label betweenIndices.linearAllocationSize qword at rbp-24
	label betweenIndices.newLetters qword at rbp-32
	label betweenIndices.newLettersLength qword at rbp-40
	label betweenIndices.lettersLengthSum qword at rbp-48
	label betweenIndices.indicesList qword at rbp-56
	label betweenIndices.lettersBetween qword at rbp-64
	label betweenIndices.startIndex qword at rbp-72
	label betweenIndices.endIndex qword at rbp-80
	label betweenIndices.betweenLength qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [betweenIndices.letters], rcx
	mov [betweenIndices.startIndex], rdx
	mov [betweenIndices.endIndex], r8


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
	mov rcx, [betweenIndices.letters]	
	call letterLength
	add rsp, 8*8
	mov [betweenIndices.lettersLength], rax




	mov r8, [betweenIndices.endIndex]
	mov r9, [betweenIndices.startIndex]
	sub r8, r9
	add r8, 1b
	mov [betweenIndices.betweenLength], r8


	mov rcx, [betweenIndices.betweenLength]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [betweenIndices.lettersBetween], rax


	mov rsi, [betweenIndices.letters]
	mov r9, [betweenIndices.startIndex]
	add rsi, r9

	mov rdi, [betweenIndices.lettersBetween]
	mov rcx, [betweenIndices.betweenLength]
	cld
	rep movsb

	

	mov rsi, letterTerminator
	mov rdi, [betweenIndices.lettersBetween]
	add rdi, [betweenIndices.betweenLength]
	mov rcx, 1
	cld
	rep movsb



	mov rax, [betweenIndices.lettersBetween]

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


letters.copyLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*7);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label copyLetters.letters qword at rbp-8 
	label copyLetters.lettersLength qword at rbp-16
	label copyLetters.linearAllocationSize qword at rbp-24
	label copyLetters.newLetters qword at rbp-32
	label copyLetters.newLettersLength qword at rbp-40
	label copyLetters.lettersLengthSum qword at rbp-48
	label copyLetters.appendedLetters qword at rbp-56
	;label copyLetters.lettersBufferForward qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [copyLetters.letters], rcx



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
	mov rcx, [copyLetters.letters]	
	call letterLength
	add rsp, 8*8
	mov [copyLetters.lettersLength], rax

	

	mov rcx, [copyLetters.lettersLength]
	add rcx, 1b							; Trailing 0
	sub rsp, 8*8
	call allocate.linear
	add rsp, 8*8
	mov [copyLetters.newLetters], rax
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;allocate rcx, copyLetters.newLetters

	mov rsi, [copyLetters.letters]
	mov rdi, [copyLetters.newLetters]
	cld
	mov rcx, [copyLetters.lettersLength]
	rep movsb



	mov rsi, letterTerminator
	mov rdi, [copyLetters.newLetters]
	add rdi, [copyLetters.lettersLength]
	mov rcx, 1
	cld
	rep movsb

	.end:

	mov rax, [copyLetters.newLetters]

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

