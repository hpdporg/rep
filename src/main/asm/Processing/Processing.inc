


section '.data' data readable writeable align 16




	;Flags
	;REPLACE_INSERT	REPLACE_BETWEEN




section '.text' code readable writeable executable align 16


replacement:
namespace replacement
replacement.lettersWithList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*20);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lettersWithList.heapAddress qword at rbp-8  
	label lettersWithList.handleAllocatedMemory qword at rbp-16
	label lettersWithList.matchFlow qword at rbp-24 
	label lettersWithList.list qword at rbp-32
	label lettersWithList.matchAddr qword at rbp-40
	label lettersWithList.letters qword at rbp-48
	label lettersWithList.flags qword at rbp-56
	label lettersWithList.lettersAlloc qword at rbp-64
	label lettersWithList.matchingIndex qword at rbp-72
	label lettersWithList.matchResultsList qword at rbp-80
	label lettersWithList.startMatchFound qword at rbp-88
	label lettersWithList.matchFoundCount qword at rbp-96
	label lettersWithList.lettersLength qword at rbp-104
	label lettersWithList.matchingEnd qword at rbp-112
	label lettersWithList.startIndex qword at rbp-120
	label lettersWithList.endIndex qword at rbp-128
	label lettersWithList.lettersIndex qword at rbp-136
	label lettersWithList.newLetters qword at rbp-144
	label lettersWithList.nextListVal qword at rbp-152
	label lettersWithList.lettersBetweenIndices qword at rbp-160
	
	
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersWithList.flags], rcx
	mov [lettersWithList.letters], rdx
	mov [lettersWithList.list], r8
	mov [lettersWithList.matchResultsList], r9


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
	mov [lettersWithList.lettersIndex], rcx		; Begin as 0
	mov [lettersWithList.newLetters], rcx
	mov [lettersWithList.nextListVal], rcx


	

	mov r8, [lettersWithList.flags]
	bt r8, 0b					; REPLACE between
	jnc lettersWithList.replaceInsert		; Replace as insert at indices
	

	sub rsp, 8*8
	mov rcx, [lettersWithList.letters]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersWithList.lettersLength], rax



	.nextMatchResult:
	mov rcx, [lettersWithList.lettersIndex]
	mov rdx, [lettersWithList.lettersLength]
	cmp rcx, rdx
	jnl lettersWithList.endMatchResultsList
	
	mov rbx,  [lettersWithList.matchResultsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jl lettersWithList.replacingOrNotReplacingVal

	mov r10, [lettersWithList.lettersLength]
	mov r11,  [lettersWithList.lettersIndex]
	add r10, r11
	add r10, 1b								; Decreased later
	mov [lettersWithList.startIndex], r10



	jmp lettersWithList.nonReplacedVal

	.replacingOrNotReplacingVal:





	sub rsp, 8*8
	mov rcx, [lettersWithList.matchResultsList]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersWithList.startIndex], rax


	sub rsp, 8*8
	mov rcx, [lettersWithList.matchResultsList]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersWithList.endIndex], rax




	

	mov rcx, [lettersWithList.lettersIndex]
	mov rdx, [lettersWithList.startIndex]
	cmp rcx, rdx
	jnl lettersWithList.appendListVal
	.nonReplacedVal:

	mov rbx, [lettersWithList.matchResultsList]
	add rbx, List.index
	mov rcx, [rbx]
	sub rcx, 10b
	mov [rbx], rcx						; Go back since not used




	sub rsp, 8*8
	mov r8, [lettersWithList.startIndex]
	sub r8, 1b
	mov rdx, [lettersWithList.lettersIndex]
	mov rcx, [lettersWithList.letters]
	call letters.betweenIndices
	add rsp, 8*8
	mov [lettersWithList.lettersBetweenIndices], rax
	
	sub rsp, 8*8
	mov rdx, [lettersWithList.lettersBetweenIndices]
	mov rcx, [lettersWithList.newLetters]
	call letters.appendLetters
	add rsp, 8*8
	mov [lettersWithList.newLetters], rax

	sub rsp, 8*8
	mov rcx, [lettersWithList.lettersBetweenIndices]
	call letters.letterLength
	add rsp, 8*8
	mov r8, [lettersWithList.lettersIndex]
	add r8, rax
	mov [lettersWithList.lettersIndex], r8






	jmp lettersWithList.nextMatchResult
	.appendListVal:





	mov rbx, [lettersWithList.list]
	mov r9, rbx
	add rbx, List.index
	add r9, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r9]
	cmp rcx, rdx
	jl lettersWithList.getNextListVal

	sub rsp, 8*8
	mov rcx, [lettersWithList.list]
	call list.resetIndex
	add rsp, 8*8

	.getNextListVal:

	sub rsp, 8*8
	mov rcx, [lettersWithList.list]
	call list.getNextItem
	add rsp, 8*8
	mov [lettersWithList.nextListVal], rax


	sub rsp, 8*8
	mov rdx, [lettersWithList.nextListVal]
	mov rcx, [lettersWithList.newLetters]
	call letters.appendLetters
	add rsp, 8*8
	mov [lettersWithList.newLetters], rax




	mov rdx, [lettersWithList.endIndex]
	add rdx, 1b
	mov [lettersWithList.lettersIndex], rdx


	

	jmp lettersWithList.nextMatchResult
	.endMatchResultsList:


	.replaceInsert:					; TO-DO


	mov rax, [lettersWithList.newLetters]


	lettersWithList.end:


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