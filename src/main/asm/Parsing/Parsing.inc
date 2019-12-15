


section '.data' data readable writeable align 16


	struc Parsing
		label .
		.delimiter dq 0		; Delimiter being used between rep items
		.baseRepOffset dq 0	; Indentation offset used in Rep
		.repOffset dq 0		; Indentation offset used in Rep
		.endDelimiter dq 0	; End of an entry delimiter i.e. newline
		.index dq 0 		; Index of what is being parsed
		.unParsedIndex dq 0 	; Index before being parsed
		.lineRefCount dq 0 	; Count of Refs on line
		.multilineRefCount dq 0 ; Count of Refs on this line that use multiline (letters)
		.parsingRefs dq 0	; Refs being parsed, if any. A list
		.nestedParsingRefs dq 0	; Nested Parsing refs, if any. A list
		.parsingDefinedRef dq 0	; Defined Ref being parsed, if any
		.flags dq 0		; PARSING_ flags
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
	newlineUnixLetters db 10,0		; '\r\n',0
	newlineWinLetters db 13,10,0		; '\r\n',0	; TO-DO: Handle both. 
	tabLetters db 9,0			;'\t',0



	; Flags
	; PARSING_AT_LETTERS	PARSING_AT_DELIMITER	PARSING_AT_NEWLINE


	; Debug msgs
	buildingRepMsg db 'Building Rep..',0
	baseRepOffsetAtLettersMsg db 'Base Rep Offset is at Letters..',0
	buildNestedRepListMsg db 'Building nested rep List..',0
	refAsParamMsg db 'Ref as param',0
	indexMsg db 'Index:',0
	endIndexMsg db 'EndIndex:',0
	parsedLettersMsg db 'Parsed letters:',0	
	startingParseRefMsg db 'ParseRef starting..',0
	lastRefMsg db 'Last ref:',0
	repOffsetMsg db 'Rep offset:',0
	baseRepOffsetMsg db 'Base Rep offset:',0
	atNewLineMsg db 'At newline.',0
	notAtNewLineMsg db 'Not at newline.',0
	atDelimiterOrLettersMsg db 'At delimiter or Letters',0	
	atDelimiterMsg db 'At delimiter',0
	atLettersMsg db 'At letters.',0
	alreadyRegisteredMsg db 'Already Registered',0
	newRegisteredValueMsg db 'New Registered Value',0
	newRegisteredDefinedRefMsg db 'New Registered Defined Ref',0
	gettingRegisteredRefMsg db 'Getting existing Registered Ref..',0


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
	add rbx, Parsing.repOffset
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
	add rbx, Parsing.unParsedIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.lineRefCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.multilineRefCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.parsingRefs
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.nestedParsingRefs
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.parsingDefinedRef
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Parsing.flags
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

parsing.getNextMatchOrDelimiter:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getNextMatchOrDelimiter.heapAddress qword at rbp-8  
	label getNextMatchOrDelimiter.handleAllocatedMemory qword at rbp-16
	label getNextMatchOrDelimiter.parsing qword at rbp-24 
	label getNextMatchOrDelimiter.matchIndex qword at rbp-32
	label getNextMatchOrDelimiter.matches qword at rbp-40
	label getNextMatchOrDelimiter.letters qword at rbp-48
	label getNextMatchOrDelimiter.matchList qword at rbp-56
	label getNextMatchOrDelimiter.parsedLetters qword at rbp-64
	label getNextMatchOrDelimiter.parsePassFlag qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getNextMatchOrDelimiter.parsing], rcx
	mov [getNextMatchOrDelimiter.letters], rdx	

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
	mov [getNextMatchOrDelimiter.heapAddress], rax
	add rsp, 8*4




	mov rcx, 0
	mov [getNextMatchOrDelimiter.parsedLetters], rcx		; Begin as 0
	mov [getNextMatchOrDelimiter.matchIndex], rcx			; Begin as 0
	mov [getNextMatchOrDelimiter.parsePassFlag], rcx			; 0 delimiter, then newline if no next delimiter

	.nextMatchAttempt:

	sub rsp, 8*8
	call [newMatches]
	add rsp, 8*8
	mov [getNextMatchOrDelimiter.matches], rax

	mov rbx, [getNextMatchOrDelimiter.matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [getNextMatchOrDelimiter.matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx

	mov r8, [getNextMatchOrDelimiter.parsePassFlag]
	cmp r8, 0
	je getNextMatchOrDelimiter.useDelimiter
	mov rdx, newlineUnixLetters

	jmp getNextMatchOrDelimiter.newContainsRangeItem
	.useDelimiter:

	mov rbx, [getNextMatchOrDelimiter.parsing]
	add rbx, Parsing.delimiter
	mov rdx, [rbx]
	.newContainsRangeItem:
	sub rsp, 8*8
	mov rbx, [getNextMatchOrDelimiter.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [getNextMatchOrDelimiter.parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	mov rdx, [getNextMatchOrDelimiter.letters]
	add rdx, r8
	mov rcx, [getNextMatchOrDelimiter.matches]
	call [getMatches]
	add rsp, 8*8
	mov [getNextMatchOrDelimiter.matchList], rax


	mov rbx,[getNextMatchOrDelimiter.matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	jne getNextMatchOrDelimiter.hasNext			; No next

	mov rcx, [getNextMatchOrDelimiter.parsePassFlag]
	cmp rcx, 0
	jne getNextMatchOrDelimiter.endParsing			; No next, already tried delimiter and newline in match

	mov rdx, 1b						; Newline instead of tab this time
	mov [getNextMatchOrDelimiter.parsePassFlag], rdx

	sub rsp, 8*8
	mov r8, [getNextMatchOrDelimiter.matches]
	mov rdx, 0
	mov rcx, [getNextMatchOrDelimiter.heapAddress]
	call [HeapFree]
	add rsp, 8*8

	jmp getNextMatchOrDelimiter.nextMatchAttempt		; Now try newline

	.hasNext:

	
	sub rsp, 8*8
	mov rcx, [getNextMatchOrDelimiter.matchList]
	call [getNextItem]
	add rsp, 8*8
	mov [getNextMatchOrDelimiter.matchIndex], rax


	sub rsp, 8*8
	mov r8, [getNextMatchOrDelimiter.matchIndex]
	sub r8, 1b					; Do not include delimiter
	mov rbx, [getNextMatchOrDelimiter.parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	add r8, rdx
	mov rbx, [getNextMatchOrDelimiter.parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [getNextMatchOrDelimiter.letters]
	call [lettersBetweenIndices]	
	add rsp, 8*8
	mov [getNextMatchOrDelimiter.parsedLetters], rax


	
	
	.endParsing:


	mov r8, [getNextMatchOrDelimiter.matchIndex]
	mov rbx, [getNextMatchOrDelimiter.parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [getNextMatchOrDelimiter.matchIndex]
	add rdx, rcx						; Do not skip delimiter
	mov [rbx], rdx


	.end:

	sub rsp, 8*8
	mov r8, [getNextMatchOrDelimiter.matches]
	mov rdx, 0
	mov rcx, [getNextMatchOrDelimiter.heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [getNextMatchOrDelimiter.parsedLetters]



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
	sub rsp, (8*13);+(8*6)

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
	label parseRep.nextRef qword at rbp-104
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



	mov rbx, [parseRep.parsing]
	add rbx, Parsing.endIndex
	mov rcx, [rbx]
	mov rdx, 0
	cmp rcx, rdx
	jne parseRep.endIndexExists			; Define Parsing endIndex




	sub rsp, 8*8
	mov rcx, [parseRep.letters]
	call [letterLength]
	add rsp, 8*8
	mov rbx, [parseRep.parsing]
	add rbx, Parsing.endIndex
	mov [rbx], rax

	.endIndexExists:				; Parsing endIndex already defined

	.nextVal:
	mov rbx, [parseRep.parsing]
	mov rdx, rbx
	add rdx, Parsing.index
	mov rcx, [rdx]
	add rbx, Parsing.endIndex
	mov r8, [rbx]
	cmp rcx, r8
	jnle parseRep.end				; Don't go past end

	sub rsp, 8*8
	mov rcx, indexMsg
	call [debugLetters]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [parseRep.parsing]
	mov rdx, rbx
	add rdx, Parsing.index
	mov rcx, [rdx]
	call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [parseRep.refRegistry]
	mov rdx, [parseRep.letters]
	mov rcx, [parseRep.parsing]
	call next
	add rsp, 8*8
	mov [parseRep.nextRef], rax



	sub rsp, 8*8
	mov r8, [parseRep.refRegistry]
	mov rdx, [parseRep.nextRef]
	mov rcx, [parseRep.parsing]
	call buildRep
	add rsp, 8*8
	
	;parseNext
		; tab
		; newline
		; letters
			; parseRef
				; getRegistered
	;buildrep
	


	.end:

	;dbgmov rax,0;[parseRep.parsedLetters]



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
	sub rsp, (8*14);+(8*6)

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
	label next.nextRef qword at rbp-104
	label next.beforeMatchIndex qword at rbp-112

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


	mov rcx, 0
	mov [next.nextRef], rcx			; Begin as 0


	mov rbx, [next.parsing]
	mov rdx, rbx
	add rbx, Parsing.index
	add rdx, Parsing.unParsedIndex
	mov rcx, [rbx]
	mov [rdx], rcx				; Maintain unParsed index

	
	sub rsp, 8*8
	mov rdx, newlineUnixLetters;newlineWinLetters
	mov rcx, [next.letters]
	mov rbx, [next.parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [hasMatch]
	add rsp, 8*8
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx	
	je next.notAtNewLine			; No newline



	sub rsp, 8*8
	mov rdx, newlineUnixLetters;newlineWinLetters
	mov rcx, [next.letters]
	mov rbx, [next.parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
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
	mov rcx, notAtNewLineMsg
	call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [next.parsing]
	add r8, Parsing.delimiter
	mov rdx, [r8]
	mov rcx, [next.letters]
	mov rbx, [next.parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [hasMatch]
	add rsp, 8*8
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx	
	je next.notAtDelimiter			; No delimiter

	sub rsp, 8*8
	mov rcx, atDelimiterOrLettersMsg
	call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [next.parsing]
	add r8, Parsing.delimiter
	mov rdx, [r8]
	mov rcx, [next.letters]
	mov rbx, [next.parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [getNextMatchIndex]
	add rsp, 8*8
	
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx				; At tab or non-default delimiter
	je next.atDelimiter

	.notAtDelimiter:


	sub rsp, 8*8
	mov rcx, 5653
	call [debugNumMsg]
	add rsp, 8*8



	sub rsp, 8*8
	mov r8, [next.refRegistry]
	mov rdx, [next.letters]
	mov rcx, [next.parsing]
	call parseRef
	add rsp, 8*8
	mov [next.nextRef], rax

	sub rsp, 8*8
	mov rcx, 99653
	call [debugNumMsg]
	add rsp, 8*8


	jmp next.atLetters

	.atNewLine:

	sub rsp, 8*8
	mov rcx, atNewLineMsg
	call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, newlineUnixLetters;newlineWinLetters
	call [letterLength]
	add rsp, 8*8
	mov [next.parsedLettersLength], rax	; Cache length


	mov rbx, [next.parsing]
	add rbx, Parsing.flags
	mov rcx, 1b				; PARSING_AT_NEWLINE
	mov [rbx], rcx

	jmp next.increaseIndex

	.atDelimiter:

	sub rsp, 8*8
	mov rcx, atDelimiterMsg
	call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [next.parsing]
	add r8, Parsing.delimiter
	mov rcx, [r8]
	call [letterLength]
	add rsp, 8*8
	mov [next.parsedLettersLength], rax	; Cache length


	mov rbx, [next.parsing]
	add rbx, Parsing.flags
	mov rcx, 10b				; PARSING_AT_DELIMITER
	mov [rbx], rcx

	jmp next.increaseIndex
	
	.atLetters:

	sub rsp, 8*8
	mov rcx, atLettersMsg
	call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [next.parsedLetters]
	call [letterLength]
	add rsp, 8*8
	mov [next.parsedLettersLength], rax	

	mov rbx, [next.parsing]
	add rbx, Parsing.flags
	mov rcx, 100b				; PARSING_AT_LETTERS
	mov [rbx], rcx



	jmp next.end				; parseRef increases Parsing index


	.increaseIndex:


	mov rbx, [next.parsing]
	add rbx, Parsing.index
	mov rcx, [rbx]
	mov rdx, [next.parsedLettersLength]
	add rcx, rdx
	mov [rbx], rcx				; Increment Parsing index



	jmp next.end


	






	



	








	mov rcx, [next.lettersIndex]
	mov r8, [next.parsedLettersLength]
	add rcx, r8
	mov [next.lettersIndex], rcx		; Increment letters index



	jmp next.endParsedValue





	mov rdx, [next.parsing]
	;add rdx, Parsing.parsingRef
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



	.endParsedValue:


	.end:

	mov rax, [next.nextRef]



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
	sub rsp, (8*13);+(8*6)

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
	label buildRep.nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [buildRep.parsing], rcx
	mov [buildRep.nextRef], rdx	
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


	sub rsp, 8*8
	mov rcx, buildingRepMsg
	call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [buildRep.refRegistry]
	mov rdx, [buildRep.nextRef]
	mov rcx, [buildRep.parsing]
	call buildBaseRepOffset
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [buildRep.refRegistry]
	mov rdx, [buildRep.nextRef]
	mov rcx, [buildRep.parsing]
	call buildNestedRepList
	add rsp, 8*8




	sub rsp, 8*8
	mov r8, [buildRep.refRegistry]
	mov rdx, [buildRep.nextRef]
	mov rcx, [buildRep.parsing]
	call parseLists
	add rsp, 8*8


	;list
	;val
	;defined
	


	.end:

	;dbgmov rax,0;[buildRep.parsedLetters]



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

parsing.buildBaseRepOffset:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label buildBaseRepOffset.heapAddress qword at rbp-8  
	label buildBaseRepOffset.handleAllocatedMemory qword at rbp-16
	label buildBaseRepOffset.parsing qword at rbp-24 
	label buildBaseRepOffset.matchIndex qword at rbp-32
	label buildBaseRepOffset.newRef qword at rbp-40
	label buildBaseRepOffset.letters qword at rbp-48
	label buildBaseRepOffset.nextNewlineIndex qword at rbp-56
	label buildBaseRepOffset.parsedLetters qword at rbp-64
	label buildBaseRepOffset.lettersIndex qword at rbp-72
	label buildBaseRepOffset.refRegistry qword at rbp-80
	label buildBaseRepOffset.newLineLetterLength qword at rbp-88
	label buildBaseRepOffset.matchingStartIndex qword at rbp-96
	label buildBaseRepOffset.nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [buildBaseRepOffset.parsing], rcx
	mov [buildBaseRepOffset.nextRef], rdx	
	mov [buildBaseRepOffset.refRegistry], r8

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



	; Flags
	; PARSING_AT_LETTERS	PARSING_AT_DELIMITER	PARSING_AT_NEWLINE
	
	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.flags
	mov rcx, [rbx]
	mov r8, 1b
	cmp rcx, r8
	je buildBaseRepOffset.atNewline


	mov r8, 10b
	cmp rcx, r8
	je buildBaseRepOffset.atDelimiter


	mov r8, 100b
	cmp rcx, r8
	je buildBaseRepOffset.atLetters


	jmp buildBaseRepOffset.end
	.atNewline:

	sub rsp, 8*8
	mov r8, [buildBaseRepOffset.refRegistry]
	mov rdx, [buildBaseRepOffset.nextRef]
	mov rcx, [buildBaseRepOffset.parsing]
	call resetNesting
	add rsp, 8*8

	jmp buildBaseRepOffset.end
	.atDelimiter:

	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.baseRepOffset
	mov rdx, [rbx]
	cmp rcx, rdx
	jle buildBaseRepOffset.increaseRepOffset


	jmp buildBaseRepOffset.end
	.increaseRepOffset:				; Increase only when it does not coiincide with base

	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx

	jmp buildBaseRepOffset.end
	.atLetters:

	sub rsp, 8*8
	mov rcx, baseRepOffsetAtLettersMsg
	call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx

	sub rsp, 8*8
	mov rcx, rcx
	call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	call [debugNumMsg]
	add rsp, 8*8

	; TO-DO: Multiline


	jmp buildBaseRepOffset.end

	.end:


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

parsing.resetNesting:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label resetNesting.heapAddress qword at rbp-8  
	label resetNesting.handleAllocatedMemory qword at rbp-16
	label resetNesting.parsing qword at rbp-24 
	label resetNesting.matchIndex qword at rbp-32
	label resetNesting.newRef qword at rbp-40
	label resetNesting.letters qword at rbp-48
	label resetNesting.nextNewlineIndex qword at rbp-56
	label resetNesting.parsedLetters qword at rbp-64
	label resetNesting.lettersIndex qword at rbp-72
	label resetNesting.refRegistry qword at rbp-80
	label resetNesting.newLineLetterLength qword at rbp-88
	label resetNesting.matchingStartIndex qword at rbp-96
	label resetNesting.nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [resetNesting.parsing], rcx
	mov [resetNesting.nextRef], rdx	
	mov [resetNesting.refRegistry], r8

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


	mov rbx, [resetNesting.parsing]
	add rbx, Parsing.repOffset
	mov rcx, 0
	mov [rbx], rcx

	mov rbx, [resetNesting.parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, 0
	mov [rbx], rcx

	.end:

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

parsing.buildNestedRepList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label buildNestedRepList.heapAddress qword at rbp-8  
	label buildNestedRepList.handleAllocatedMemory qword at rbp-16
	label buildNestedRepList.parsing qword at rbp-24 
	label buildNestedRepList.matchIndex qword at rbp-32
	label buildNestedRepList.newRef qword at rbp-40
	label buildNestedRepList.lastRef qword at rbp-48
	label buildNestedRepList.nextNewlineIndex qword at rbp-56
	label buildNestedRepList.parsedLetters qword at rbp-64
	label buildNestedRepList.lettersIndex qword at rbp-72
	label buildNestedRepList.refRegistry qword at rbp-80
	label buildNestedRepList.newLineLetterLength qword at rbp-88
	label buildNestedRepList.matchingStartIndex qword at rbp-96
	label buildNestedRepList.nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [buildNestedRepList.parsing], rcx
	mov [buildNestedRepList.nextRef], rdx	
	mov [buildNestedRepList.refRegistry], r8

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
	mov rcx, buildNestedRepListMsg
	call [debugLettersMsg]
	add rsp, 8*8



	mov rdx, [buildNestedRepList.nextRef]
	cmp rdx, 0
	je buildNestedRepList.end			; Not at a new Ref

	sub rsp, 8*8
	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	call [debugNumMsg]
	add rsp, 8*8


	mov rbx, [buildBaseRepOffset.parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	mov rdx, 1b
	cmp rcx, rdx
	jg buildNestedRepList.refAsParam

	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.parsingRefs
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov rcx, [rdx]
	cmp rcx, 0
	jne buildNestedRepList.notFirstRef


	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.baseRepOffset
	mov [rbx], rcx					; Also increase baseRepOffset if needed when first
	

	sub rsp, 8*8
	mov rcx, repOffsetMsg
	call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, baseRepOffsetMsg
	call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.baseRepOffset
	mov rcx, [rbx]					; Also increase baseRepOffset if needed when first
	call [debugNumMsg]
	add rsp, 8*8

	.notFirstRef:



	sub rsp, 8*8
	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [resetIndex]				; TO-DO: Remove this
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [buildNestedRepList.nextRef]
	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.repOffset
	mov rdx, [rbx]
	mov rbx, [buildNestedRepList.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [lastItemNesting]
	add rsp, 8*8



	jmp buildNestedRepList.end
	.refAsParam:

	sub rsp, 8*8
	mov rcx, refAsParamMsg
	call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [buildNestedRepList.refRegistry]
	mov rdx, [buildNestedRepList.nextRef]
	mov rcx, [buildNestedRepList.parsing]
	call getLastRef
	add rsp, 8*8
	mov [buildNestedRepList.lastRef], rax

	sub rsp, 8*8
	mov rcx, lastRefMsg
	call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [buildNestedRepList.lastRef]
	call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [buildNestedRepList.nextRef]
	mov rbx, [buildNestedRepList.lastRef]
	add rbx, Ref.list
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	jmp buildNestedRepList.end

	.end:
	mov rax, [buildNestedRepList.nextRef]


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

; Returns 0 when none
parsing.getLastRef:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getLastRef.heapAddress qword at rbp-8  
	label getLastRef.handleAllocatedMemory qword at rbp-16
	label getLastRef.parsing qword at rbp-24 
	label getLastRef.matchIndex qword at rbp-32
	label getLastRef.newRef qword at rbp-40
	label getLastRef.letters qword at rbp-48
	label getLastRef.nextNewlineIndex qword at rbp-56
	label getLastRef.parsedLetters qword at rbp-64
	label getLastRef.lettersIndex qword at rbp-72
	label getLastRef.refRegistry qword at rbp-80
	label getLastRef.newLineLetterLength qword at rbp-88
	label getLastRef.matchingStartIndex qword at rbp-96
	label getLastRef.nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getLastRef.parsing], rcx
	mov [getLastRef.nextRef], rdx	
	mov [getLastRef.refRegistry], r8

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

	
	mov rbx, [getLastRef.parsing]
	add rbx, Parsing.parsingRefs
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov rcx, [rdx]
	cmp rcx, 0
	je getLastRef.firstRef

	mov rbx, [getLastRef.parsing]
	add rbx, Parsing.parsingRefs
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	mov rbx, [getLastRef.parsing]
	add rbx, Parsing.parsingRefs
	mov r9, [rbx]
	add r9, List.index
	sub r8, 1b
	mov [r9], r8					; Set index - 1

	sub rsp, 8*8
	mov rbx, [getLastRef.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [getNextItem]
	add rsp, 8*8
	
	jmp getLastRef.end
	.firstRef:


	mov rax, 0
	jmp getLastRef.end

	.end:

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

parsing.parseLists:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label parseLists.heapAddress qword at rbp-8  
	label parseLists.handleAllocatedMemory qword at rbp-16
	label parseLists.parsing qword at rbp-24 
	label parseLists.matchIndex qword at rbp-32
	label parseLists.newRef qword at rbp-40
	label parseLists.letters qword at rbp-48
	label parseLists.nextNewlineIndex qword at rbp-56
	label parseLists.parsingRefsList qword at rbp-64
	label parseLists.lettersIndex qword at rbp-72
	label parseLists.refRegistry qword at rbp-80
	label parseLists.newLineLetterLength qword at rbp-88
	label parseLists.matchingStartIndex qword at rbp-96
	label parseLists.nextRef qword at rbp-104
	label parseLists.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parseLists.parsing], rcx
	mov [parseLists.nextRef], rdx	
	mov [parseLists.refRegistry], r8

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
	mov r8, [parseLists.refRegistry]
	mov rdx, [parseLists.nextRef]
	mov rcx, [parseLists.parsing]
	call defineLists
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [parseLists.refRegistry]
	mov rdx, [parseLists.nextRef]
	mov rcx, [parseLists.parsing]
	call defineNonLists
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [parseLists.refRegistry]
	mov rdx, [parseLists.nextRef]
	mov rcx, [parseLists.parsing]
	call defineListParams
	add rsp, 8*8


	;definelists
	;definenonlists (can still be overriden in subsequent passes)
	;definelistparams


	



	mov rax, [parseLists.nextRef]
	.end:

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

parsing.defineLists:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label defineLists.heapAddress qword at rbp-8  
	label defineLists.handleAllocatedMemory qword at rbp-16
	label defineLists.parsing qword at rbp-24 
	label defineLists.matchIndex qword at rbp-32
	label defineLists.newRef qword at rbp-40
	label defineLists.letters qword at rbp-48
	label defineLists.nextNewlineIndex qword at rbp-56
	label defineLists.parsingRefsList qword at rbp-64
	label defineLists.prevItem qword at rbp-72
	label defineLists.refRegistry qword at rbp-80
	label defineLists.item qword at rbp-88
	label defineLists.prevItemNesting qword at rbp-96
	label defineLists.nextRef qword at rbp-104
	label defineLists.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [defineLists.parsing], rcx
	mov [defineLists.nextRef], rdx	
	mov [defineLists.refRegistry], r8

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
	mov [defineLists.prevItem], rcx			; Begin as 0
	mov [defineLists.item], rcx			; Begin as 0
	mov [defineLists.prevItemNesting], rcx
	mov [defineLists.nesting], rcx

	mov rbx, [defineLists.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [defineLists.parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [defineLists.parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	;definelists
	;defineLists (can still be overriden in subsequent passes)
	;defineLists


	.nextRefItem:
	mov rbx, [defineLists.parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl defineLists.endParsingRefsList


	sub rsp, 8*8
	mov rcx, [defineLists.parsingRefsList]
	call [getNextItemNesting]
	add rsp, 8*8
	mov [defineLists.nesting], rax

	sub rsp, 8*8
	mov rcx, [defineLists.parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	mov [defineLists.item], rax

	mov rcx, [defineLists.nesting]
	mov rdx, [defineLists.prevItemNesting]
	sub rcx, rdx
	mov r8, 1b
	cmp rcx, r8
	jne defineLists.listRefNotFound

	mov rbx, [defineLists.prevItem]
	add rbx, Ref.flags
	mov rdx, 10b
	mov [rbx], rdx						; Found a List REF_LIST


	.listRefNotFound:
	mov rbx, [defineLists.item]
	mov [defineLists.prevItem], rbx
	mov rbx, [defineLists.nesting]
	mov [defineLists.prevItemNesting], rbx
	


	jmp defineLists.nextRefItem
	.endParsingRefsList:


	.end:
	mov rax, [defineLists.nextRef]


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

parsing.defineNonLists:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label defineNonLists.heapAddress qword at rbp-8  
	label defineNonLists.handleAllocatedMemory qword at rbp-16
	label defineNonLists.parsing qword at rbp-24 
	label defineNonLists.matchIndex qword at rbp-32
	label defineNonLists.newRef qword at rbp-40
	label defineNonLists.letters qword at rbp-48
	label defineNonLists.nextNewlineIndex qword at rbp-56
	label defineNonLists.parsingRefsList qword at rbp-64
	label defineNonLists.lettersIndex qword at rbp-72
	label defineNonLists.refRegistry qword at rbp-80
	label defineNonLists.newLineLetterLength qword at rbp-88
	label defineNonLists.matchingStartIndex qword at rbp-96
	label defineNonLists.nextRef qword at rbp-104
	label defineNonLists.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [defineNonLists.parsing], rcx
	mov [defineNonLists.nextRef], rdx	
	mov [defineNonLists.refRegistry], r8

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

	


	mov rbx, [defineNonLists.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [defineNonLists.parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [defineNonLists.parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	;definelists
	;definenonlists (can still be overriden in subsequent passes)
	;defineNonLists


	.nextRefItem:
	mov rbx, [defineNonLists.parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl defineNonLists.endParsingRefsList


	
	sub rsp, 8*8
	mov rcx, [defineNonLists.parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	add rax, Ref.flags
	mov r8, [rax]
	mov rdx, 10b
	cmp r8, rdx
	jne defineNonLists.notList

	jmp defineNonLists.nextRefItem
	.notList:

	mov rdx, 100b
	cmp r8, rdx
	jne defineNonLists.notDefinedRef

	jmp defineNonLists.nextRefItem
	.notDefinedRef:

	mov rdx, 1000b
	cmp r8, rdx
	jne defineNonLists.notRefFilter

	jmp defineNonLists.nextRefItem
	.notRefFilter:

	mov rdx, 1b
	mov [rax], rdx					; Found a val ref


	jmp defineNonLists.nextRefItem
	.endParsingRefsList:


	.end:
	mov rax, [defineNonLists.nextRef]
	

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

parsing.defineListParams:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label defineListParams.heapAddress qword at rbp-8  
	label defineListParams.handleAllocatedMemory qword at rbp-16
	label defineListParams.parsing qword at rbp-24 
	label defineListParams.matchIndex qword at rbp-32
	label defineListParams.newRef qword at rbp-40
	label defineListParams.letters qword at rbp-48
	label defineListParams.nextNewlineIndex qword at rbp-56
	label defineListParams.parsingRefsList qword at rbp-64
	label defineListParams.lettersIndex qword at rbp-72
	label defineListParams.refRegistry qword at rbp-80
	label defineListParams.newLineLetterLength qword at rbp-88
	label defineListParams.matchingStartIndex qword at rbp-96
	label defineListParams.nextListRef qword at rbp-104
	label defineListParams.nesting qword at rbp-112
	label defineListParams.convergedCount qword at rbp-120
	label defineListParams.nextRef qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [defineListParams.parsing], rcx
	mov [defineListParams.nextRef], rdx	
	mov [defineListParams.refRegistry], r8

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

	


	mov rbx, [defineListParams.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [defineListParams.parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [defineListParams.parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	;definelists
	;defineListParams (can still be overriden in subsequent passes)
	;definelistparams


	.nextRefItem:
	mov rbx, [defineListParams.parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl defineListParams.endParsingRefsList


	sub rsp, 8*8
	mov rcx, [defineListParams.parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	mov [defineListParams.nextListRef], rax

	mov rbx, [defineListParams.nextListRef]
	add rbx, Ref.flags
	mov rcx, [rbx]
	mov r8, 10b
	cmp rcx, r8
	jne defineListParams.nextRefItem		; List Ref not reached

	mov rbx, [defineListParams.parsingRefsList]
	add rbx, List.index
	mov rcx, [rbx]
	sub rcx, 1b
	mov [rbx], rcx					; Go back 1
	
	sub rsp, 8*8
	mov rcx, [defineListParams.parsingRefsList]
	call [getConvergedItemCount]
	add rsp, 8*8
	mov [defineListParams.convergedCount], rax

	mov rbx, [defineListParams.nextListRef]
	add rbx, Ref.list
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	mov r9, [defineListParams.convergedCount]
	cmp r8, r9
	jnle defineListParams.nextRefItem		; ListRef's item count is not less than or equal to converged count


	sub rsp, 8*8
	mov rdx, [defineListParams.nextRef]
	mov rbx, [defineListParams.nextListRef]
	add rbx, Ref.list
	mov rcx, [rbx]
	call [newLastItem]				; NextRef must be missing at this point
	add rsp, 8*8


	jmp defineListParams.end
	.endParsingRefsList:



	
	.end:
	mov rax, [defineListParams.nextRef]

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



	sub rsp, 8*8
	mov rcx, startingParseRefMsg
	call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [parseRef.letters]
	mov rcx, [parseRef.parsing]
	call getNextMatchOrDelimiter
	add rsp, 8*8
	mov [parseRef.parsedLetters], rax

	
	sub rsp, 8*8
	mov rcx, parsedLettersMsg
	call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [parseRef.parsedLetters]
	call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [parseRef.refRegistry]
	mov rdx, [parseRef.parsedLetters]
	mov rcx, [parseRef.parsing]
	call getRegisteredValue
	add rsp, 8*8
	mov [parseRef.newRef], rax

	sub rsp, 8*8
	mov rcx, 33
	call [debugNumMsg]
	add rsp, 8*8


	jmp parseRef.end






















	mov rbx, [parseRef.parsing]
	add rbx, Parsing.index
	mov rcx, [rbx]
	mov [parseRef.matchingStartIndex], rcx	; Cache use later



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
	mov rdx, [parseRef.parsedLetters]
	mov rcx, [parseRef.refRegistry]
	call refRegistry.getRegisteredDefinedRef
	add rsp, 8*8
	add rax, Ref.definedRefFlags
	mov r8, [rax]
	mov rbx, [parseRef.newRef]
	add rbx, Ref.definedRefFlags
	mov [rbx], r8					; Copy flags

	sub rsp, 8*8
	mov rbx, [parseRef.parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]
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
	mov rbx, [parseRef.parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]
	mov rdx, [parseRef.newRef]
	mov rcx, [parseRef.refRegistry]
	call refRegistry.newLastRegisteredRef
	add rsp, 8*8

	
	.newRefRegistered:



	.parsingRefBlankOrStillParsing:		; Need to put Ref in Parsing also when not there
	mov rdx, [parseRef.parsing]
	;add rdx, Parsing.parsingRef
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
	mov rcx, 100b				; REF_DEFINED
	je parseRef.newDefinedRef


	mov rdx, [parseRef.parsing]
	;add rdx, Parsing.parsingRef
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

	mov rax, [parseRef.newRef]


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

parsing.getRegisteredValue:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getRegisteredValue.heapAddress qword at rbp-8  
	label getRegisteredValue.handleAllocatedMemory qword at rbp-16
	label getRegisteredValue.parsing qword at rbp-24 
	label getRegisteredValue.matchIndex qword at rbp-32
	label getRegisteredValue.newRef qword at rbp-40
	label getRegisteredValue.letters qword at rbp-48
	label getRegisteredValue.nextNewlineIndex qword at rbp-56
	label getRegisteredValue.parsedLetters qword at rbp-64
	label getRegisteredValue.lettersIndex qword at rbp-72
	label getRegisteredValue.refRegistry qword at rbp-80
	label getRegisteredValue.newLineLetterLength qword at rbp-88
	label getRegisteredValue.matchingStartIndex qword at rbp-96
	label getRegisteredValue.refFlags qword at rbp-104
	label getRegisteredValue.definedRefFlags qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getRegisteredValue.parsing], rcx
	mov [getRegisteredValue.parsedLetters], rdx	
	mov [getRegisteredValue.refRegistry], r8

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

	mov rcx, 1b
	mov [getRegisteredValue.refFlags], rcx			; Begin as REF_VALUE
	mov rcx, 0
	mov [getRegisteredValue.definedRefFlags], rcx		; Begin as 0


	sub rsp, 8*8
	mov rcx, gettingRegisteredRefMsg
	call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [getRegisteredValue.parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]						; Used with defined Refs only
	mov rdx, [getRegisteredValue.parsedLetters]
	mov rcx, [getRegisteredValue.refRegistry]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0						
	je getRegisteredValue.newLastRegisteredRef		; Non-existent Ref
	cmp rax, 1b
	je getRegisteredValue.newLastRegisteredDefinedRef	; Non-existent DefinedRef

	.alreadyDefined:

	mov [getRegisteredValue.newRef], rax

	sub rsp, 8*8
	mov rcx, alreadyRegisteredMsg
	call [debugLettersMsg]
	add rsp, 8*8
	

	jmp getRegisteredValue.end

	.newLastRegisteredDefinedRef:

	sub rsp, 8*8
	mov rcx, newRegisteredDefinedRefMsg
	call [debugLettersMsg]
	add rsp, 8*8

	mov r8, 100b						; REF_DEFINED
	mov [getRegisteredValue.refFlags], r8

	sub rsp, 8*8
	mov rdx, [getRegisteredValue.parsedLetters]
	mov rcx, [getRegisteredValue.refRegistry]
	call refRegistry.getRegisteredDefinedRef
	add rsp, 8*8
	add rax, Ref.definedRefFlags
	mov r8, [rax]
	mov [getRegisteredValue.definedRefFlags], r8
	

	jmp getRegisteredValue.newLastRegisteredVal
	.newLastRegisteredRef:					; refFlags is 1 REF_VALUE (may become REF_LIST later)


	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [getRegisteredValue.newRef], rax

	sub rsp, 8*8
	mov rcx, newRegisteredValueMsg
	call [debugLettersMsg]
	add rsp, 8*8
	
	
	jmp getRegisteredValue.placeRefInRefRegistry

	.newLastRegisteredVal:

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [getRegisteredValue.newRef], rax




	.placeRefInRefRegistry:

	mov rbx, [getRegisteredValue.newRef]
	add rbx, Ref.flags
	mov r8, [getRegisteredValue.refFlags]			; REF_DEFINED or undefined at this point
	mov [rbx], r8

	mov rbx, [getRegisteredValue.newRef]
	mov r8, [getRegisteredValue.definedRefFlags]
	add rbx, Ref.definedRefFlags
	mov [rbx], r8					; Copy defined refflags or 0



	mov rbx, [getRegisteredValue.newRef]
	add rbx, Ref.ref
	mov r8, [getRegisteredValue.parsedLetters]
	mov [rbx], r8

	sub rsp, 8*8
	mov rbx, [getRegisteredValue.parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]						; Used with defined Refs only
	mov rdx, [getRegisteredValue.newRef]
	mov rcx, [getRegisteredValue.refRegistry]
	call refRegistry.newLastRegisteredRef
	add rsp, 8*8








	.end:

	
	mov rax, [getRegisteredValue.newRef]


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
;parseRefvalue
;parseReflist
;parseRefdefined


end namespace