


section '.data' data readable writeable align 16


	struc Parsing
		label .
		.delimiter dq 0		; Delimiter being used between rep items
		.baseRepOffset dq 0	; Indentation offset used in Rep
		.endDelimiter dq 0	; End of an entry delimiter i.e. newline
		.index dq 0 		; Index of what is being parsed
		.parsingRef dq 0	; Ref being parsed, if any
		.nestedParsingRef dq 0	; Nested Parsing ref, if any
		.parsingDefinedRef dq 0	; Defined Ref being parsed, if any
		.endIndex dq 0		; End of what is being parsed
	end struc


	

	; Used with address offsets
	virtual at 0
		Parsing Parsing
	end virtual

	; ---- Structures
	;element Element


	
	letterTerminator db 0
	pathSepLetters db '\',0
	directoryContentsLetters db '\*',0
	currentDirLetter db '.',0
	containingDirLetters db '..',0
	newlineWinLetters db 13,10,0		; '\r\n',0
	tabLetters db 9,0			;'\t',0
	

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
	add rcx, Parsing.endIndex
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4





	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.delimiter
	mov rdx, tabLetters
	mov [rbx], rdx
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.baseRepOffset
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.endDelimiter
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.index
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.parsingRef
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.nestedParsingRef
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.parsingDefinedRef
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.endIndex
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

parsing.getNext:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNext.heapAddress qword at rbp-8  
	label getNext.handleAllocatedMemory qword at rbp-16
	label getNext.parsing qword at rbp-24 
	label getNext.matchIndex qword at rbp-32
	label getNext.matches qword at rbp-40
	label getNext.letters qword at rbp-48
	label getNext.matchList qword at rbp-56
	label getNext.parsedLetters qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNext.parsing], rcx
	mov [getNext.letters], rdx	

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
	mov [getNext.heapAddress], rax
	add rsp, 8*4




	mov rcx, 0
	mov [getNext.parsedLetters], rcx		; Begin as 0
	mov [getNext.matchIndex], rcx			; Begin as 0

	sub rsp, 8*8
	call [newMatches]
	add rsp, 8*8
	mov [getNext.matches], rax

	mov rbx, [getNext.matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [getNext.matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx


	sub rsp, 8*8
	mov rbx, [getNext.parsing]
	add rbx, Parsing.delimiter
	mov rdx, [rbx]
	mov rbx, [getNext.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [getNext.parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	mov rdx, [getNext.letters]
	add rdx, r8
	mov rcx, [getNext.matches]
	call [getMatches]
	add rsp, 8*8
	mov [getNext.matchList], rax


	mov rbx,[getNext.matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	je getNext.endParsing			; No next

	
	sub rsp, 8*8
	mov rcx, [getNext.matchList]
	call [getNextItem]
	add rsp, 8*8
	mov [getNext.matchIndex], rax


	sub rsp, 8*8
	mov r8, [getNext.matchIndex]
	sub r8, 1b					; Do not include delimiter
	mov rbx, [getNext.parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	add r8, rdx
	mov rbx, [getNext.parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [getNext.letters]
	call [lettersBetweenIndices]	
	add rsp, 8*8
	mov [getNext.parsedLetters], rax


	
	
	.endParsing:

	sub rsp, 8*8
	mov rbx, [getNext.parsing]
	add rbx, Parsing.delimiter
	mov rcx, [rbx]
	call [letterLength]
	add rsp, 8*8
	mov r8, [getNext.matchIndex]
	mov rbx, [getNext.parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [getNext.matchIndex]
	add rdx, rcx
	add rdx, rax				; Delimiter length
	mov [rbx], rdx


	.end:

	sub rsp, 8*8
	mov r8, [getNext.matches]
	mov rdx, 0
	mov rcx, [getNext.heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [getNext.parsedLetters]



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


; parseRep can call parseNext as many times as it needs in order to traverse the Rep
; It also can call buildRep when there is a new Ref required
parsing.parseRep:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*12);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label parseRep.heapAddress qword at rbp-8  
	label parseRep.handleAllocatedMemory qword at rbp-16
	label parseRep.parsing qword at rbp-24 
	label parseRep.matchIndex qword at rbp-32
	label parseRep.newRef qword at rbp-40
	label parseRep.letters qword at rbp-48
	label parseRep.nextNewlineIndex qword at rbp-56
	label parseRep.parsedLetters qword at rbp-64
	label parseRep.lettersIndex qword at rbp-72
	label parseRep.refRegistry qword at rbp-80
	label parseRep.newLineLetterLength qword at rbp-88
	label parseRep.matchingStartIndex qword at rbp-96
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parseRep.parsing], rcx
	mov [parseRep.letters], rdx	
	mov [parseRep.refRegistry], r8

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
	mov r8, [parseRep.refRegistry]
	mov rdx, [parseRep.letters]
	mov rcx, [parseRep.parsing]
	call next
	add rsp, 8*8


	;parseNext
		; tab
		; newline
		; letters
			; parseRef
	;buildrep
	


	.end:

	mov rax,0;[parseRep.parsedLetters]



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

parsing.next:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*12);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label next.heapAddress qword at rbp-8  
	label next.handleAllocatedMemory qword at rbp-16
	label next.parsing qword at rbp-24 
	label next.matchIndex qword at rbp-32
	label next.newRef qword at rbp-40
	label next.letters qword at rbp-48
	label next.nextNewlineIndex qword at rbp-56
	label next.parsedLetters qword at rbp-64
	label next.lettersIndex qword at rbp-72
	label next.refRegistry qword at rbp-80
	label next.newLineLetterLength qword at rbp-88
	label next.parsedLettersLength qword at rbp-96
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [next.parsing], rcx
	mov [next.letters], rdx	
	mov [next.refRegistry], r8

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




	; compareValNewline
	; compareValTab
	; valLetters





















	jmp next.end


	mov rcx, 0
	mov [next.lettersIndex], rcx		; Begin as 0


	sub rsp, 8*8
	mov rcx, newlineWinLetters
	call [letterLength]
	add rsp, 8*8
	mov [next.newLineLetterLength], rax	


	sub rsp, 8*8
	mov rdx, newlineWinLetters
	mov rcx, [next.letters]
	mov r8, [next.lettersIndex]
	add rcx, r8
	call [getNextMatchIndex]
	add rsp, 8*8
	mov [next.nextNewlineIndex], rax
	
	mov rcx, 0
	mov rdx, [next.nextNewlineIndex]
	cmp rdx, rcx				; At newline
	je next.atNewLine


	.notAtNewLine:

	sub rsp, 8*8
	mov r8, [next.parsing]
	add r8, Parsing.delimiter
	mov rdx, [r8]
	mov rcx, [next.letters]
	mov r8, [next.lettersIndex]
	add rcx, r8
	call [hasMatch]
	add rsp, 8*8
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx	
	je next.notAtDelimiter			; No delimiter

	sub rsp, 8*8
	mov r8, [next.parsing]
	add r8, Parsing.delimiter
	mov rdx, [r8]
	mov rcx, [next.letters]
	mov r8, [next.lettersIndex]
	add rcx, r8
	call [getNextMatchIndex]
	add rsp, 8*8
	
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx				; At tab
	je next.atDelimiter

	.notAtDelimiter:



	sub rsp, 8*8
	mov r8, [next.refRegistry]
	mov rdx, [next.letters]
	mov rcx, [next.parsing]
	call parseRef
	add rsp, 8*8
	mov [next.parsedLetters], rax



	sub rsp, 8*8
	mov rcx, [next.parsedLetters]
	call [letterLength]
	add rsp, 8*8
	mov [next.parsedLettersLength], rax	



	mov rcx, [next.lettersIndex]
	mov r8, [next.parsedLettersLength]
	add rcx, r8
	mov [next.lettersIndex], rcx		; Increment letters index



	jmp next.endParsedValue


	.atNewLine:


	mov rdx, [next.parsing]
	add rdx, Parsing.parsingRef
	mov rbx, [rdx]
	add rbx, Ref.flags
	mov rcx, [rbx]
	cmp rcx, 0				; 0, must be list 
	jne next.refNotList

	mov rdx, 10b
	mov [rbx], rdx				; REF_LIST


	.refNotList:

	mov rcx, [next.lettersIndex]
	mov r8, [next.newLineLetterLength]
	add rcx, r8
	mov [next.lettersIndex], rcx		; Increment letters index
	mov rdx, [next.parsing]
	add rdx, Parsing.index
	mov rcx, [rdx]
	add rcx, r8
	mov [rdx], rcx				; Increment Parsing index


	jmp next.endParsedValue

	.atDelimiter:

	mov rcx, [next.lettersIndex]
	mov r8, 1b
	add rcx, r8
	mov [next.lettersIndex], rcx		; Increment letters index
	mov rdx, [next.parsing]
	add rdx, Parsing.index
	mov rcx, [rdx]
	add rcx, r8
	mov [rdx], rcx				; Increment Parsing index


	.endParsedValue:


	.end:

	mov rax, 0;[next.parsedLetters]



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

parsing.buildRep:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*12);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label buildRep.heapAddress qword at rbp-8  
	label buildRep.handleAllocatedMemory qword at rbp-16
	label buildRep.parsing qword at rbp-24 
	label buildRep.matchIndex qword at rbp-32
	label buildRep.newRef qword at rbp-40
	label buildRep.letters qword at rbp-48
	label buildRep.nextNewlineIndex qword at rbp-56
	label buildRep.parsedLetters qword at rbp-64
	label buildRep.lettersIndex qword at rbp-72
	label buildRep.refRegistry qword at rbp-80
	label buildRep.newLineLetterLength qword at rbp-88
	label buildRep.matchingStartIndex qword at rbp-96
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [buildRep.parsing], rcx
	mov [buildRep.letters], rdx	
	mov [buildRep.refRegistry], r8

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


	


	.end:

	mov rax,0;[buildRep.parsedLetters]



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



parsing.parseRef:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*12);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label parseRef.heapAddress qword at rbp-8  
	label parseRef.handleAllocatedMemory qword at rbp-16
	label parseRef.parsing qword at rbp-24 
	label parseRef.matchIndex qword at rbp-32
	label parseRef.newRef qword at rbp-40
	label parseRef.letters qword at rbp-48
	label parseRef.nextNewlineIndex qword at rbp-56
	label parseRef.parsedLetters qword at rbp-64
	label parseRef.lettersIndex qword at rbp-72
	label parseRef.refRegistry qword at rbp-80
	label parseRef.newLineLetterLength qword at rbp-88
	label parseRef.matchingStartIndex qword at rbp-96
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parseRef.parsing], rcx
	mov [parseRef.letters], rdx	
	mov [parseRef.refRegistry], r8

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





	jmp parseRef.end





	mov rbx, [parseRef.parsing]
	add rbx, Parsing.index
	mov rcx, [rbx]
	mov [parseRef.matchingStartIndex], rcx	; Cache use later

	sub rsp, 8*8
	mov rdx, [parseRef.letters]
	mov rcx, [parseRef.parsing]
	call getNext
	add rsp, 8*8
	mov [parseRef.parsedLetters], rax


	sub rsp, 8*8
	mov r8, [parseRef.matchingStartIndex]	; Used with defined Refs only
	mov rdx, [parseRef.parsedLetters]
	mov rcx, [parseRef.refRegistry]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0				; Already exists
	je parseRef.newLastRegisteredRef
	cmp rax, 1b
	jne parseRef.parsingRefBlankOrStillParsing	; Already defined
	

	.newLastDefinedRef:


	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [parseRef.newRef], rax

	mov rbx, [parseRef.newRef]
	add rbx, Ref.ref
	mov r8, [parseRef.parsedLetters]
	mov [rbx], r8
	mov rbx, [parseRef.newRef]
	add rbx, Ref.repIndex
	mov rcx, [parseRef.matchingStartIndex]	; Index
	mov [rbx], rcx

	mov rbx, [parseRef.newRef]
	add rbx, Ref.flags
	mov r8, 10b				; REF_DEFINED
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [parseRef.newRef]
	mov rcx, [parseRef.refRegistry]
	call refRegistry.newLastRegisteredRef	; Uses same list as non-defined
	add rsp, 8*8


	jmp parseRef.newRefRegistered
	.newLastRegisteredRef:

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [parseRef.newRef], rax

	mov rbx, [parseRef.newRef]
	add rbx, Ref.ref
	mov r8, [parseRef.parsedLetters]
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [parseRef.newRef]
	mov rcx, [parseRef.refRegistry]
	call refRegistry.newLastRegisteredRef
	add rsp, 8*8

	
	.newRefRegistered:



	.parsingRefBlankOrStillParsing:		; Need to put Ref in Parsing also when not there
	mov rdx, [parseRef.parsing]
	add rdx, Parsing.parsingRef
	mov r8, [rdx]
	mov rcx, 0
	cmp r8, rcx
	je parseRef.parsingRefBlank
	

	.parsingRefNotBlank:


	.parsingRefBlank:

	
	mov rbx, [parseRef.newRef]
	add rbx, Ref.flags
	mov r8, [rbx]
	cmp r8, rcx
	mov rcx, 10b				; REF_DEFINED
	je parseRef.newDefinedRef


	mov rdx, [parseRef.parsing]
	add rdx, Parsing.parsingRef
	mov r8, [parseRef.newRef]
	mov [rdx], r8


	jmp parseRef.end
	.newDefinedRef:


	mov rdx, [parseRef.parsing]
	add rdx, Parsing.parsingDefinedRef
	mov r8, [parseRef.newRef]
	mov [rdx], r8

	jmp parseRef.end

	.existingRef:

	;compare parsedLetters, parsingRef
	;compare parsingRef list
	; new last list item


	.end:

	;mov rax,[parseRef.parsedLetters]	; Put back?
	mov rax,0;[parseRef.parsedLetters]



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

;parseRefWithFlags calls below three parse calls
;getParsedLettersRefFlag?
;parserefvalue
;parsereflist
;parserefdefined


end namespace