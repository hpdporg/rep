


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
	newlineLetters dq 0


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
	parseListsMsg db 'Parsing Lists..',0
	defineListsMsg	db 'Define Lists..',0
	defineNonListsMsg	db 'Define NonLists..',0
	defineListParamsMsg	db 'Define List Params..',0
	prevItemWasListMsg	db 'Prev Item was a List: ',0


section '.text' code readable writeable executable align 16



parsing:
namespace parsing
new:
namespace new
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
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
	mov [heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, Parsing.endIndex
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4





	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.delimiter
	mov rdx, tabLetters
	mov [rbx], rdx
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.baseRepOffset
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.repOffset
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.endDelimiter
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.index
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.unParsedIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.lineRefCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.multilineRefCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.parsingRefs
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.nestedParsingRefs
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.parsingDefinedRef
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Parsing.endIndex
	mov rax, 0
	mov [rbx], rax
	



	;lea rax, [list]
	;lea rcx, [list.indexedItemIndex]

	;sub rcx, rax
	;add rcx, 1000b

	;cld

	;lea rsi, [list]
	;mov rdi, [storage.handleAllocatedMemory]

	;rep movsb


	mov rax, [handleAllocatedMemory]


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

getNext:
namespace getNext
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*8);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label matches qword at rbp-40
	label lettersAddr qword at rbp-48
	label matchList qword at rbp-56
	label parsedLetters qword at rbp-64
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [lettersAddr], rdx	

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
	mov [heapAddress], rax
	add rsp, 8*4




	mov rcx, 0
	mov [parsedLetters], rcx		; Begin as 0
	mov [matchIndex], rcx			; Begin as 0

	sub rsp, 8*8
	call [newMatches]
	add rsp, 8*8
	mov [matches], rax

	mov rbx, [matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx


	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.delimiter
	mov rdx, [rbx]
	mov rbx, [matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	mov rdx, [lettersAddr]
	add rdx, r8
	mov rcx, [matches]
	call [getMatches]
	add rsp, 8*8
	mov [matchList], rax


	mov rbx,[matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	je endParsing			; No next

	
	sub rsp, 8*8
	mov rcx, [matchList]
	call [getNextItem]
	add rsp, 8*8
	mov [matchIndex], rax


	sub rsp, 8*8
	mov r8, [matchIndex]
	sub r8, 1b					; Do not include delimiter
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	add r8, rdx
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [lettersAddr]
	call [lettersBetweenIndices]	
	add rsp, 8*8
	mov [parsedLetters], rax


	
	
	endParsing:

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.delimiter
	mov rcx, [rbx]
	call [letterLength]
	add rsp, 8*8
	mov r8, [matchIndex]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [matchIndex]
	add rdx, rcx
	add rdx, rax				; Delimiter length
	mov [rbx], rdx


	completed:

	sub rsp, 8*8
	mov r8, [matches]
	mov rdx, 0
	mov rcx, [heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [parsedLetters]



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

getNextMatchOrDelimiter:
namespace getNextMatchOrDelimiter
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label matches qword at rbp-40
	label letters qword at rbp-48
	label matchList qword at rbp-56
	label parsedLetters qword at rbp-64
	label parsePassFlag qword at rbp-72
	label nextNewlineIndex qword at rbp-80
	label nextDelimiterIndex qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [letters], rdx	

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
	mov [heapAddress], rax
	add rsp, 8*4




	mov rcx, 0
	mov [parsedLetters], rcx		; Begin as 0
	mov [matchIndex], rcx			; Begin as 0
	mov [parsePassFlag], rcx			; 0 delimiter, then newline if no next delimiter

	nextMatchAttempt:

	sub rsp, 8*8
	call [newMatches]
	add rsp, 8*8
	mov [matches], rax

	mov rbx, [matches]
	add rbx, Matches.flags
	mov rcx, 10101b
	mov [rbx], rcx
	mov rbx, [matches]
	add rbx, Matches.transformFlags
	mov rcx, 100b
	mov [rbx], rcx

	mov r8, [parsePassFlag]
	cmp r8, 0
	je useDelimiter
	mov rdx, [newlineLetters]							;	newlineUnixLetters

	jmp newContainsRangeItem
	useDelimiter:

	mov rbx, [parsing]
	add rbx, Parsing.delimiter
	mov rdx, [rbx]
	newContainsRangeItem:
	sub rsp, 8*8
	mov rbx, [matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	mov rdx, [letters]
	add rdx, r8
	mov rcx, [matches]
	call [getMatches]
	add rsp, 8*8
	mov [matchList], rax


	mov rbx,[matchList]
	add rbx, List.itemsCount
	mov rcx, 0
	mov rdx, [rbx]
	cmp rcx, rdx
	jne hasNext			; No next

	mov rcx, [parsePassFlag]
	cmp rcx, 0
	jne endParsing			; No next, already tried delimiter and newline in match

	mov rdx, 1b						; Newline instead of tab this time
	mov [parsePassFlag], rdx

	sub rsp, 8*8
	mov r8, [matches]
	mov rdx, 0
	mov rcx, [heapAddress]
	call [HeapFree]
	add rsp, 8*8

	jmp nextMatchAttempt		; Now try newline

	hasNext:						; TO-DO: Simplify this section (delimiter versus newline nearest determination)


	sub rsp, 8*8
	mov rdx, [newlineLetters]							;	newlineUnixLetters	newlineUnixLetters;newlineWinLetters
	mov rcx, [letters]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [hasMatch]
	add rsp, 8*8
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx	
	je noNextNewline			; No newline



	sub rsp, 8*8
	mov rdx, [newlineLetters]							;	newlineUnixLetters;newlineWinLetters
	mov rcx, [letters]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [getNextMatchIndex]
	add rsp, 8*8
	mov [nextNewlineIndex], rax

	sub rsp, 8*8
	mov rcx, [matchList]
	call [getNextItem]
	add rsp, 8*8
	mov [matchIndex], rax


	sub rsp, 8*8
	mov rcx, 8929
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [matchIndex]
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [nextNewlineIndex]
	;call [debugNumMsg]
	add rsp, 8*8

	mov rcx, [matchIndex]
	mov rdx, [nextNewlineIndex]
	cmp rcx, rdx
	jle matchIndexDetermined

	mov [matchIndex], rdx
	jmp matchIndexDetermined		; When newline comes before delimiter, use it instead

	noNextNewline:

	
	sub rsp, 8*8
	mov rcx, [matchList]
	call [getNextItem]
	add rsp, 8*8
	mov [matchIndex], rax

	matchIndexDetermined:


	sub rsp, 8*8
	mov r8, [matchIndex]
	sub r8, 1b					; Do not include delimiter
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	add r8, rdx
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [letters]
	call [lettersBetweenIndices]	
	add rsp, 8*8
	mov [parsedLetters], rax


	
	
	endParsing:


	mov r8, [matchIndex]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rdx, [rbx]
	mov rcx, [matchIndex]
	add rdx, rcx						; Do not skip delimiter
	mov [rbx], rdx


	completed:

	sub rsp, 8*8
	mov r8, [matches]
	mov rdx, 0
	mov rcx, [heapAddress]
	call [HeapFree]
	add rsp, 8*8


	mov rax, [parsedLetters]



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

; parseRep can call parseNext as many times as it needs in order to traverse the Rep
; It also can call buildRep when there is a new Ref required
parseRep:
namespace parseRep
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistry qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [letters], rdx	
	mov [refRegistry], r8

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
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.endIndex
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8


	mov rbx, [parsing]
	add rbx, Parsing.endIndex
	mov rcx, [rbx]
	mov rdx, 0
	cmp rcx, rdx
	jne endIndexExists			; Define Parsing endIndex




	sub rsp, 8*8
	mov rcx, [letters]
	call [letterLength]
	add rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.endIndex
	mov [rbx], rax

	endIndexExists:				; Parsing endIndex already defined

	nextVal:
	mov rbx, [parsing]
	mov rdx, rbx
	add rdx, Parsing.index
	mov rcx, [rdx]
	add rbx, Parsing.endIndex
	mov r8, [rbx]
	cmp rcx, r8
	jnle completed				; Don't go past end

	sub rsp, 8*8
	mov rcx, indexMsg
	;call [debugLetters]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [parsing]
	mov rdx, rbx
	add rdx, Parsing.index
	mov rcx, [rdx]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, 5
	call [numAsLetters]					; There is a bug here, alignment? Something uninitialized in numAsLetters? Remove this call which re-aligns..
	add rsp, 8*8
	mov rax, rax

	sub rsp, 8*8
	mov rcx, 389
	;call [debugNumMsg]				; There is a bug here, alignment? Something uninitialized in numAsLetters? Remove this call which re-aligns..
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [refRegistry]
	mov rdx, [letters]
	mov rcx, [parsing]
	call next
	add rsp, 8*8
	mov [nextRef], rax



	sub rsp, 8*8
	mov r8, [refRegistry]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call buildRep
	add rsp, 8*8
	
	;parseNext
		; tab
		; newline
		; letters
			; parseRef
				; getRegistered
	;buildrep
	


	completed:

	

	;dbgmov rax,0;[parsedLetters]



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

next:
namespace next
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistry qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label parsedLettersLength qword at rbp-96
	label nextRef qword at rbp-104
	label beforeMatchIndex qword at rbp-112

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [letters], rdx	
	mov [refRegistry], r8

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
	mov [nextRef], rcx			; Begin as 0


	mov rbx, [parsing]
	mov rdx, rbx
	add rbx, Parsing.index
	add rdx, Parsing.unParsedIndex
	mov rcx, [rbx]
	mov [rdx], rcx				; Maintain unParsed index

	
	sub rsp, 8*8
	mov rdx, [newlineLetters]							;	newlineUnixLetters;newlineWinLetters
	mov rcx, [letters]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [hasMatch]
	add rsp, 8*8
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx	
	je notAtNewLine			; No newline



	sub rsp, 8*8
	mov rdx, [newlineLetters]							;	newlineUnixLetters;newlineWinLetters
	mov rcx, [letters]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [getNextMatchIndex]
	add rsp, 8*8
	mov [nextNewlineIndex], rax



	mov rcx, 0
	mov rdx, [nextNewlineIndex]
	cmp rdx, rcx				; At newline
	je atNewLine

	notAtNewLine:

	sub rsp, 8*8
	mov rcx, notAtNewLineMsg
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [parsing]
	add r8, Parsing.delimiter
	mov rdx, [r8]
	mov rcx, [letters]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [hasMatch]
	add rsp, 8*8
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx	
	je notAtDelimiter			; No delimiter

	sub rsp, 8*8
	mov rcx, atDelimiterOrLettersMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [parsing]
	add r8, Parsing.delimiter
	mov rdx, [r8]
	mov rcx, [letters]
	mov rbx, [parsing]
	add rbx, Parsing.index
	mov r8, [rbx]
	add rcx, r8
	call [getNextMatchIndex]
	add rsp, 8*8
	
	mov rcx, 0
	mov rdx, rax
	cmp rdx, rcx				; At tab or non-default delimiter
	je atDelimiter

	notAtDelimiter:


	sub rsp, 8*8
	mov rcx, 5653
	;call [debugNumMsg]
	add rsp, 8*8



	sub rsp, 8*8
	mov r8, [refRegistry]
	mov rdx, [letters]
	mov rcx, [parsing]
	call parseRef
	add rsp, 8*8
	mov [nextRef], rax

	sub rsp, 8*8
	mov rcx, 99653
	;call [debugNumMsg]
	add rsp, 8*8


	jmp atLetters

	atNewLine:

	sub rsp, 8*8
	mov rcx, atNewLineMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [newlineLetters]							;	newlineUnixLetters;newlineWinLetters
	call [letterLength]
	add rsp, 8*8
	mov [parsedLettersLength], rax	; Cache length


	mov rbx, [parsing]
	add rbx, Parsing.flags
	mov rcx, 1b				; PARSING_AT_NEWLINE
	mov [rbx], rcx

	jmp increaseIndex

	atDelimiter:

	sub rsp, 8*8
	mov rcx, atDelimiterMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [parsing]
	add r8, Parsing.delimiter
	mov rcx, [r8]
	call [letterLength]
	add rsp, 8*8
	mov [parsedLettersLength], rax	; Cache length


	mov rbx, [parsing]
	add rbx, Parsing.flags
	mov rcx, 10b				; PARSING_AT_DELIMITER
	mov [rbx], rcx

	jmp increaseIndex
	
	atLetters:

	sub rsp, 8*8
	mov rcx, atLettersMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [parsedLetters]
	call [letterLength]
	add rsp, 8*8
	mov [parsedLettersLength], rax	

	mov rbx, [parsing]
	add rbx, Parsing.flags
	mov rcx, 100b				; PARSING_AT_LETTERS
	mov [rbx], rcx



	jmp completed				; parseRef increases Parsing index


	increaseIndex:


	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rcx, [rbx]
	mov rdx, [parsedLettersLength]
	add rcx, rdx
	mov [rbx], rcx				; Increment Parsing index



	jmp completed


	






	



	








	mov rcx, [lettersIndex]
	mov r8, [parsedLettersLength]
	add rcx, r8
	mov [lettersIndex], rcx		; Increment letters index



	jmp endParsedValue





	mov rdx, [parsing]
	;add rdx, Parsing.parsingRef
	mov rbx, [rdx]
	add rbx, Ref.flags
	mov rcx, [rbx]
	cmp rcx, 0				; 0, must be list 
	jne refNotList

	mov rdx, 10b
	mov [rbx], rdx				; REF_LIST


	refNotList:

	mov rcx, [lettersIndex]
	mov r8, [newLineLetterLength]
	add rcx, r8
	mov [lettersIndex], rcx		; Increment letters index
	mov rdx, [parsing]
	add rdx, Parsing.index
	mov rcx, [rdx]
	add rcx, r8
	mov [rdx], rcx				; Increment Parsing index


	jmp endParsedValue



	endParsedValue:


	completed:

	mov rax, [nextRef]



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

buildRep:
namespace buildRep
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call buildBaseRepOffset
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call buildNestedRepList
	add rsp, 8*8



	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call parseLists
	add rsp, 8*8


	;list
	;val
	;defined
	


	completed:

	;dbgmov rax,0;[parsedLetters]



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

buildBaseRepOffset:
namespace buildBaseRepOffset
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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
	
	mov rbx, [parsing]
	add rbx, Parsing.flags
	mov rcx, [rbx]
	mov r8, 1b
	cmp rcx, r8
	je atNewline


	mov r8, 10b
	cmp rcx, r8
	je atDelimiter


	mov r8, 100b
	cmp rcx, r8
	je atLetters


	jmp completed
	atNewline:

	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call resetNesting
	add rsp, 8*8

	jmp completed
	atDelimiter:

	mov rbx, [parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	mov rbx, [parsing]
	add rbx, Parsing.baseRepOffset
	mov rdx, [rbx]
	cmp rcx, rdx
	jle increaseRepOffset


	jmp completed
	increaseRepOffset:				; Increase only when it does not coiincide with base

	mov rbx, [parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx

	jmp completed
	atLetters:

	sub rsp, 8*8
	mov rcx, baseRepOffsetAtLettersMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx

	sub rsp, 8*8
	mov rcx, rcx
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8

	; TO-DO: Multiline


	jmp completed

	completed:


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

resetNesting:
namespace resetNesting
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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


	mov rbx, [parsing]
	add rbx, Parsing.repOffset
	mov rcx, 0
	mov [rbx], rcx

	mov rbx, [parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, 0
	mov [rbx], rcx

	completed:

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

buildNestedRepList:
namespace buildNestedRepList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lastRef qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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
	;call [debugLettersMsg]
	add rsp, 8*8




	mov rdx, [nextRef]
	cmp rdx, 0
	je completed			; Not at a new Ref


	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8


	mov rbx, [parsing]
	add rbx, Parsing.lineRefCount
	mov rcx, [rbx]
	mov rdx, 1b
	cmp rcx, rdx
	jg refAsParam

	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov rcx, [rdx]
	cmp rcx, 0
	jne notFirstRef


	mov rbx, [parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	mov rbx, [parsing]
	add rbx, Parsing.baseRepOffset
	mov [rbx], rcx					; Also increase baseRepOffset if needed when first
	

	sub rsp, 8*8
	mov rcx, repOffsetMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.repOffset
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, baseRepOffsetMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.baseRepOffset
	mov rcx, [rbx]					; Also increase baseRepOffset if needed when first
	;call [debugNumMsg]
	add rsp, 8*8

	notFirstRef:



	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [resetIndex]				; TO-DO: Remove this
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [nextRef]
	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.repOffset
	mov rdx, [rbx]
	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [lastItemNesting]
	add rsp, 8*8



	jmp completed
	refAsParam:

	sub rsp, 8*8
	mov rcx, refAsParamMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call getLastRef
	add rsp, 8*8
	mov [lastRef], rax

	sub rsp, 8*8
	mov rcx, lastRefMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [lastRef]
	;call [debugNumMsg]
	add rsp, 8*8


	;mov rbx, [lastRef]
	;add rbx, Ref.flags
	;mov rdx, [rbx]
	;cmp rdx, 10b					
	;jne lastRefNotList		

	;mov rbx, [nextRef]
	;add rbx, Ref.flags
	;mov rdx, [rbx]
	;cmp rdx, 100b					; REF_DEFINED TO-DO: Handle this elsewhere? letters should not be a list param
	;je end			; Skip

	;.lastRefNotList:

	sub rsp, 8*8
	mov rdx, [nextRef]
	mov rbx, [lastRef]
	add rbx, Ref.list
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	jmp completed

	completed:
	mov rax, [nextRef]


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

; Returns 0 when none
getLastRef:
namespace getLastRef
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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

	
	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov rcx, [rdx]
	cmp rcx, 0
	je firstRef

	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov r9, [rbx]
	add r9, List.index
	sub r8, 1b
	mov [r9], r8					; Set index - 1

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	call [getNextItem]
	add rsp, 8*8
	
	jmp completed
	firstRef:


	mov rax, 0
	jmp completed

	completed:

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

parseLists:
namespace parseLists
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsingRefsList qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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
	mov rcx, parseListsMsg
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call defineLists
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call defineNonLists
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsing]
	call defineListParams
	add rsp, 8*8


	;definelists
	;definenonlists (can still be overriden in subsequent passes)
	;definelistparams


	



	mov rax, [nextRef]
	completed:

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

defineLists:
namespace defineLists
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsingRefsList qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label prevItemNesting qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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
	mov [prevItem], rcx			; Begin as 0
	mov [item], rcx			; Begin as 0
	mov [prevItemNesting], rcx
	mov [nesting], rcx


	sub rsp, 8*8
	mov rcx, defineListsMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	;definelists
	;defineLists (can still be overriden in subsequent passes)
	;defineLists


	nextRefItem:
	mov rbx, [parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endParsingRefsList

	


	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [getNextItemNesting]
	add rsp, 8*8
	mov [nesting], rax

	sub rsp, 8*8
	mov rcx, [nesting]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	mov [item], rax

	sub rsp, 8*8
	mov rbx, [item]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8


	mov rcx, [nesting]
	mov rdx, [prevItemNesting]
	sub rcx, rdx
	mov r8, 1b
	cmp rcx, r8
	jne listRefNotFound

	mov rbx, [prevItem]
	add rbx, Ref.flags
	mov rdx, 10b
	mov [rbx], rdx						; Found a List REF_LIST


	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [prevItem]
	mov rcx, [parsing]
	call propagateRefFlags					; Ensure every occurence is a List, and Ref Registry Ref also
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rcx,prevItemWasListMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [prevItem]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, rdx
	;call [debugNumMsg]
	add rsp, 8*8



	listRefNotFound:
	mov rbx, [item]
	mov [prevItem], rbx
	mov rbx, [nesting]
	mov [prevItemNesting], rbx
	


	jmp nextRefItem
	endParsingRefsList:


	completed:
	mov rax, [nextRef]


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

defineNonLists:
namespace defineNonLists
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsingRefsList qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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
	mov rcx, defineNonListsMsg
	;call [debugLettersMsg]
	add rsp, 8*8
	


	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	;definelists
	;definenonlists (can still be overriden in subsequent passes)
	;defineNonLists


	nextRefItem:
	mov rbx, [parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endParsingRefsList


	
	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	add rax, Ref.flags
	mov r8, [rax]
	mov rdx, 10b
	cmp r8, rdx
	jne notList

	jmp nextRefItem
	notList:

	mov rdx, 100b
	cmp r8, rdx
	jne notDefinedRef

	jmp nextRefItem
	notDefinedRef:

	mov rdx, 1000b
	cmp r8, rdx
	jne notRefFilter

	jmp nextRefItem
	notRefFilter:

	mov rdx, 1b
	mov [rax], rdx					; Found a val ref


	jmp nextRefItem
	endParsingRefsList:


	completed:
	mov rax, [nextRef]
	

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

defineListParams:
namespace defineListParams
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsingRefsList qword at rbp-64
	label parsingListIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextListRef qword at rbp-104
	label nesting qword at rbp-112
	label convergedCount qword at rbp-120
	label nextRef qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [nextRef], rdx	
	mov [refRegistryAddr], r8

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
	mov [parsingListIndex], rcx		; Begin as 0

	mov rcx, [nextRef]
	cmp rcx, 0
	je completed					; No ref
	
	;mov rbx, [nextRef]		; Instead of this, make sure convergedcount does not show these
	;add rbx, Ref.flags
	;mov rdx, [rbx]
	;cmp rdx, 100b					; REF_DEFINED TO-DO: Handle this elsewhere? letters should not be a list param
	;je end				; Skip


	sub rsp, 8*8
	mov rcx, defineListParamsMsg
	;call [debugLettersMsg]
	add rsp, 8*8


	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	;definelists
	;defineListParams (can still be overriden in subsequent passes)
	;definelistparams


	nextRefItem:
	mov rbx, [parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endParsingRefsList


	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	mov [nextListRef], rax




	sub rsp, 8*8
	mov rbx, [nextListRef]
	add rbx, Ref.flags
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8

	mov rbx, [nextListRef]
	add rbx, Ref.flags
	mov rcx, [rbx]
	mov r8, 10b
	cmp rcx, r8
	jne nextRefItem		; List Ref not reached

	sub rsp, 8*8
	mov rcx, 839898
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [nextListRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [parsingRefsList]
	add rbx, List.index
	mov rcx, [rbx]
	mov [parsingListIndex], rcx			; cache

	mov rbx, [parsingRefsList]
	add rbx, List.index
	mov rcx, [rbx]
	sub rcx, 1b
	mov [rbx], rcx					; Go back 1
	

	sub rsp, 8*8
	mov rbx, [parsingRefsList]
	add rbx, List.index
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, 28918
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [getConvergedItemCount]
	add rsp, 8*8
	mov [convergedCount], rax

	mov rbx, [parsingRefsList]
	add rbx, List.index
	mov rcx, [parsingListIndex]			; Restore
	mov [rbx], rcx

	sub rsp, 8*8
	mov rbx, [parsingRefsList]
	add rbx, List.index
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, 89
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [convergedCount]
	;call [debugNumMsg]
	add rsp, 8*8

	mov r9, [convergedCount]
	cmp r9, 0
	je nextRefItem			; Can this ever happen?

	mov rbx, [nextListRef]
	add rbx, Ref.list
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	mov r9, [convergedCount]
	cmp r8, r9
	jnl nextRefItem		; ListRef's item count is not less than or equal to converged count


	sub rsp, 8*8
	mov rdx, [nextRef]
	mov rbx, [nextListRef]
	add rbx, Ref.list
	mov rcx, [rbx]
	call [newLastItem]				; NextRef must be missing at this point
	add rsp, 8*8


	jmp completed
	endParsingRefsList:



	
	completed:
	mov rax, [nextRef]

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

parseRef:
namespace parseRef
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*12);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [lettersAddr], rdx	
	mov [refRegistryAddr], r8

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
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [lettersAddr]
	mov rcx, [parsing]
	call getNextMatchOrDelimiter
	add rsp, 8*8
	mov [parsedLetters], rax

	
	sub rsp, 8*8
	mov rcx, parsedLettersMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [parsedLetters]
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [parsedLetters]
	mov rcx, [parsing]
	call getRegisteredValue
	add rsp, 8*8
	mov [newRefAddr], rax

	sub rsp, 8*8
	mov rcx, 33
	;call [debugNumMsg]
	add rsp, 8*8


	jmp completed






















	mov rbx, [parsing]
	add rbx, Parsing.index
	mov rcx, [rbx]
	mov [matchingStartIndex], rcx	; Cache use later



	sub rsp, 8*8
	mov r8, [matchingStartIndex]	; Used with defined Refs only
	mov rdx, [parsedLetters]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0				; Already exists
	je newLastRegisteredRef
	cmp rax, 1b
	jne parsingRefBlankOrStillParsing	; Already defined
	

	newLastDefinedRef:


	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRefAddr], rax

	mov rbx, [newRefAddr]
	add rbx, Ref.ref
	mov r8, [parsedLetters]
	mov [rbx], r8
	mov rbx, [newRefAddr]
	add rbx, Ref.repIndex
	mov rcx, [matchingStartIndex]	; Index
	mov [rbx], rcx

	mov rbx, [newRefAddr]
	add rbx, Ref.flags
	mov r8, 10b				; REF_DEFINED
	mov [rbx], r8


	sub rsp, 8*8
	mov rdx, [parsedLetters]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredDefinedRef
	add rsp, 8*8
	add rax, Ref.definedRefFlags
	mov r8, [rax]
	mov rbx, [newRefAddr]
	add rbx, Ref.definedRefFlags
	mov [rbx], r8					; Copy flags

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]
	mov rdx, [newRefAddr]
	mov rcx, [refRegistryAddr]
	call refRegistry.newLastRegisteredRef	; Uses same list as non-defined
	add rsp, 8*8


	jmp newRefRegistered
	newLastRegisteredRef:

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRefAddr], rax

	mov rbx, [newRefAddr]
	add rbx, Ref.ref
	mov r8, [parsedLetters]
	mov [rbx], r8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]
	mov rdx, [newRefAddr]
	mov rcx, [refRegistryAddr]
	call refRegistry.newLastRegisteredRef
	add rsp, 8*8

	
	newRefRegistered:



	parsingRefBlankOrStillParsing:		; Need to put Ref in Parsing also when not there
	mov rdx, [parsing]
	;add rdx, Parsing.parsingRef
	mov r8, [rdx]
	mov rcx, 0
	cmp r8, rcx
	je parsingRefBlank
	

	parsingRefNotBlank:


	parsingRefBlank:

	
	mov rbx, [newRefAddr]
	add rbx, Ref.flags
	mov r8, [rbx]
	cmp r8, rcx
	mov rcx, 100b				; REF_DEFINED
	je newDefinedRef


	mov rdx, [parsing]
	;add rdx, Parsing.parsingRef
	mov r8, [newRefAddr]
	mov [rdx], r8


	jmp completed
	newDefinedRef:


	mov rdx, [parsing]
	add rdx, Parsing.parsingDefinedRef
	mov r8, [newRefAddr]
	mov [rdx], r8

	jmp completed

	existingRef:

	;compare parsedLetters, parsingRef
	;compare parsingRef list
	; new last list item


	completed:

	mov rax, [newRefAddr]


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

getRegisteredValue:
namespace getRegisteredValue
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRefAddr qword at rbp-40
	label lettersAddr qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label refFlags qword at rbp-104
	label definedRefFlags qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [parsedLetters], rdx	
	mov [refRegistryAddr], r8

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
	mov [refFlags], rcx			; Begin as REF_VALUE
	mov rcx, 0
	mov [definedRefFlags], rcx		; Begin as 0


	sub rsp, 8*8
	mov rcx, gettingRegisteredRefMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]						; Used with defined Refs only
	mov rdx, [parsedLetters]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0						
	je newLastRegisteredRef		; Non-existent Ref
	cmp rax, 1b
	je newLastRegisteredDefinedRef	; Non-existent DefinedRef

	alreadyDefined:

	mov [newRefAddr], rax

	sub rsp, 8*8
	mov rcx, alreadyRegisteredMsg
	;call [debugLettersMsg]
	add rsp, 8*8
	

	jmp completed

	newLastRegisteredDefinedRef:

	sub rsp, 8*8
	mov rcx, newRegisteredDefinedRefMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	mov r8, 100b						; REF_DEFINED
	mov [refFlags], r8

	sub rsp, 8*8
	mov rdx, [parsedLetters]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredDefinedRef
	add rsp, 8*8
	add rax, Ref.definedRefFlags
	mov r8, [rax]
	mov [definedRefFlags], r8
	

	jmp newLastRegisteredVal
	newLastRegisteredRef:					; refFlags is 1 REF_VALUE (may become REF_LIST later)


	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRefAddr], rax

	sub rsp, 8*8
	mov rcx, newRegisteredValueMsg
	;call [debugLettersMsg]
	add rsp, 8*8
	
	
	jmp placeRefInRefRegistry

	newLastRegisteredVal:

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRefAddr], rax




	placeRefInRefRegistry:

	mov rbx, [newRefAddr]
	add rbx, Ref.flags
	mov r8, [refFlags]			; REF_DEFINED or undefined at this point
	mov [rbx], r8

	mov rbx, [newRefAddr]
	mov r8, [definedRefFlags]
	add rbx, Ref.definedRefFlags
	mov [rbx], r8					; Copy defined refflags or 0



	mov rbx, [newRefAddr]
	add rbx, Ref.ref
	mov r8, [parsedLetters]
	mov [rbx], r8

	sub rsp, 8*8
	mov rbx, [parsing]
	add rbx, Parsing.unParsedIndex
	mov r8, [rbx]						; Used with defined Refs only
	mov rdx, [newRefAddr]
	mov rcx, [refRegistryAddr]
	call refRegistry.newLastRegisteredRef
	add rsp, 8*8








	completed:

	
	mov rax, [newRefAddr]


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


; Copy Ref flags into every occurence in the Parsing Refs and Ref Registry Lists
; Preserves Parsing List index
propagateRefFlags:
namespace propagateRefFlags
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label ref qword at rbp-32
	label newRefAddr qword at rbp-40
	label parsingList qword at rbp-48
	label parsingListIndex qword at rbp-56
	label refRegistryList qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label refFlags qword at rbp-104
	label definedRefFlags qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsing], rcx
	mov [ref], rdx	
	mov [refRegistryAddr], r8

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



	

	mov rbx, [parsing]
	add rbx, Parsing.parsingRefs
	mov rdx, [rbx]
	mov [parsingList], rdx		; Cache
	add rdx, List.index
	mov rcx, [rdx]
	mov [parsingListIndex], rcx		; Restore later



	sub rsp, 8*8
	mov r8, 0						; Used with defined Refs only
	mov rbx, [ref]
	add rbx, Ref.ref
	mov rdx, [rbx]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0						
	je noRegisteredRefValue		; Non-existent Ref
	cmp rax, 1b
	je noRegisteredRefValue		; Non-existent DefinedRef

	alreadyDefined:

	mov [newRefAddr], rax

	sub rsp, 8*8
	mov rcx, 55218989
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [newRefAddr]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [ref]
	add rbx, Ref.flags
	mov r8, [newRefAddr]
	add r8, Ref.flags
	mov r9, [rbx]
	mov [r8], r9						; Propagate into RefRegistry


	

	noRegisteredRefValue:

	sub rsp, 8*8
	mov rcx, [parsingList]
	call [resetIndex]
	add rsp, 8*8
	
	nextParsingRef:
	mov rbx, [parsingList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endParsingRefs

	sub rsp, 8*8
	mov rcx, [parsingList]
	call [getNextItem]
	add rsp, 8*8
	mov [newRefAddr], rax

	mov rbx, [ref]
	add rbx, Ref.ref
	mov r8, [newRefAddr]
	add r8, Ref.ref
	mov r9, [rbx]
	mov r10, [r8]


	sub rsp, 8*8
	mov rcx, 218989
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [ref]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [newRefAddr]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8


	mov rbx, [ref]
	add rbx, Ref.ref
	mov r8, [newRefAddr]
	add r8, Ref.ref
	mov r9, [rbx]
	mov r10, [r8]


	sub rsp, 8*8
	mov rdx, r10
	mov rcx, r9
	call [lettersSameExact]
	add rsp, 8*8	
	cmp rax, 0
	je nextParsingRef
	

	mov rbx, [ref]
	add rbx, Ref.flags
	mov r8, [newRefAddr]
	add r8, Ref.flags
	mov r9, [rbx]
	mov [r8], r9						; Propagate into Parsing Refs List Ref


	sub rsp, 8*8
	mov rcx, 213989
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [ref]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [newRefAddr]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8


	jmp nextParsingRef

	endParsingRefs:
	
	mov rbx, [parsingList]
	add rbx, List.index
	mov rcx, [parsingListIndex]
	mov [rbx], rcx						; Restore Index



	completed:



	
	mov rax, [ref]


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

;parseRefWithFlags calls below three parse calls
;getParsedLettersRefFlag?
;parseRefvalue
;parseReflist
;parseRefdefined


end namespace