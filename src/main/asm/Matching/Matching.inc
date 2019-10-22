


section '.data' data readable writeable align 16


	struc Matches
		label .
		.flags dq 0		; Matches flags
		.transformFlags dq 0	; Transform Flags
		.containsRangeList dq 0	; Contains or Range list (Contains X versus Range 0-200)
		.subRangeStartIndex dq 0	; Sub range start index
		.subRangeEndIndex dq 0	; Sub range end index
	end struc


	;Flags
	;MATCH_SUBRANGE_END_IND	MATCH_SUBRANGE_START_IND	MATCH_SUBRANGE	MATCH_TRANSFORM	MATCH_EVERY	MATCH_FIRST	MATCH_END	MATCH_START

	;Transform Flags
	;TRANSFORM_CONTAIN_OPTIONAL_COUNT	TRANSFORM_CONTAINS_SEQUENTIAL	TRANSFORM_ENDS_WITH	TRANSFORM_STARTS_WITH	TRANSFORM_CONTAINS_DISCONTINUOUS	TRANSFORM_EXCLUDES	TRANSFORM_CONTAINS	TRANSFORM_RANGE	TRANSFORM_INSENSITIVE_CASE



	struc MatchFlow
		label .
		.contains dq 0		; Contains flow
		.start dq 0		; Start match
		.end dq 0		; End match
		.firstMatch dq 0	; Contains first Match flow
		.everyMatch dq 0	; Contains every Match flow
		.matchIndexCount dq 0	; Required match index count minimum or maximum
		.startEndLength dq 0	; Start and ends matched i.e. length
	end struc



	; Used with address offsets
	virtual at 0
		Matches Matches
	end virtual

	; ---- Structures
	;element Element

	; Used with address offsets
	virtual at 0
		MatchFlow MatchFlow
	end virtual

	; ---- Structures
	;element Element






	

	

section '.text' code readable writeable executable align 16


matching:
namespace matching
matching.new:
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
	add rcx, Matches.subRangeEndIndex
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.transformFlags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.containsRangeList
	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.subRangeStartIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, Matches.subRangeEndIndex
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

matching.newMatchFlow:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*2);+(8*0)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label newMatchFlow.heapAddress qword at rbp-8  
	label newMatchFlow.handleAllocatedMemory qword at rbp-16
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
	mov [newMatchFlow.heapAddress], rax
	add rsp, 8*4
	

	mov rcx, 0
	add rcx, MatchFlow.startEndLength
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [newMatchFlow.heapAddress]
	call [ HeapAlloc] 
	mov [newMatchFlow.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.contains
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.start
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.end
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.firstMatch
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.everyMatch
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.matchIndexCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [newMatchFlow.handleAllocatedMemory]
	add rbx, MatchFlow.startEndLength
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


	mov rax, [newMatchFlow.handleAllocatedMemory]


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

matching.processFlags:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*6);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processFlags.heapAddress qword at rbp-8  
	label processFlags.handleAllocatedMemory qword at rbp-16
	label processFlags.matchFlow qword at rbp-24 
	label processFlags.matchIndexCount qword at rbp-32
	label processFlags.matchAddr qword at rbp-40
	label processFlags.letters qword at rbp-48
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processFlags.matchAddr], rcx
	

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
	call newMatchFlow
	add rsp, 8*8
	mov [processFlags.matchFlow], rax


	mov rcx, 0
	mov [processFlags.matchIndexCount], rcx		; Begin as 0

	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 0					; MATCH_START	
	jnc processFlags.endIndex

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.start
	mov rcx, 1b
	mov [rbx], rcx

	mov rcx, 1b
	mov rdx, [processFlags.matchIndexCount]
	add rdx, rcx
	mov [processFlags.matchIndexCount], rdx		; Increment


	.endIndex:
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 1b					; MATCH_END
	jnc processFlags.matchFirstOrEvery	

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.end
	mov rcx, 1b
	mov [rbx], rcx

	mov rdx, [processFlags.matchFlow]
	add rdx, MatchFlow.start
	mov r8, [rdx]
	cmp r8, 0
	je processFlags.endOnly

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.startEndLength		; MATCH start and end (length of contains)
	mov rcx, 1b
	mov [rbx], rcx


	.endOnly:

	mov rcx, 1b
	mov rdx, [processFlags.matchIndexCount]
	add rdx, rcx
	mov [processFlags.matchIndexCount], rdx		; Increment
	

	.matchFirstOrEvery:

	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 10b					; MATCH_FIRST
	jnc processFlags.everyMatch


	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.firstMatch
	mov rcx, 1b
	mov [rbx], rcx

	jmp processFlags.hasTransform

	.everyMatch:
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 11b					; MATCH_EVERY
	jnc processFlags.hasTransform

	
	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.everyMatch
	mov rcx, 1b
	mov [rbx], rcx



	.hasTransform:
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.flags
	mov r8, [rbx]
	bt r8, 100b					; MATCH_TRANSFORM
	jnc processFlags.defineMatchIndexCounts

	
	mov rbx, [processFlags.matchAddr]
	add rbx, Matches.transformFlags
	mov r8, [rbx]
	bt r8, 10b					; TRANSFORM_CONTAINS
	jnc processFlags.defineMatchIndexCounts	

	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.contains
	mov rcx, 1b
	mov [rbx], rcx

	.defineMatchIndexCounts:

	mov rdx, [processFlags.matchIndexCount]
	mov rbx, [processFlags.matchFlow]
	add rbx, MatchFlow.matchIndexCount
	mov [rbx], rdx

	.end:

	mov rax, [processFlags.matchFlow]



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



matching.get:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label get.heapAddress qword at rbp-8  
	label get.handleAllocatedMemory qword at rbp-16
	label get.matchFlow qword at rbp-24 
	label get.list qword at rbp-32
	label get.matchAddr qword at rbp-40
	label get.letters qword at rbp-48
	label get.containsRangeList qword at rbp-56
	label get.containsAddr qword at rbp-64
	label get.matchingIndex qword at rbp-72
	label get.containsLength qword at rbp-80
	label get.startMatchFound qword at rbp-88
	label get.matchFoundCount qword at rbp-96
	label get.lettersLength qword at rbp-104
	label get.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [get.matchAddr], rcx
	mov [get.letters], rdx


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
	mov [get.heapAddress], rax
	add rsp, 8*4

	sub rsp, 8*8
	call list.new
	add rsp, 8*8
	mov [get.list], rax


	sub rsp, 8*8
	mov rcx, [get.letters]
	call letters.letterLength
	add rsp, 8*8
	mov [get.lettersLength], rax



	mov rbx, [get.matchAddr]
	add rbx, Matches.containsRangeList
	mov rdx, [rbx]
	mov [get.containsRangeList], rdx



	sub rsp, 8*8
	mov rcx, [get.matchAddr]
	call matching.processFlags
	add rsp, 8*8
	mov [get.matchFlow], rax
	

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.contains
	mov r8, [rbx]
	bt r8, 0b					; Match contains
	jnc get.endMatching				; Until others are supported

	
	mov rcx, 0
	mov [get.matchingIndex], rcx			; Begin at 0
	mov rcx, 0
	mov [get.matchFoundCount], rcx			; Begin as 0
	mov rcx, 0
	mov [get.startMatchFound], rcx			; Begin as 0


	get.nextMatch:


	mov rcx, [get.matchingIndex]
	mov rdx, [get.lettersLength]
	cmp rcx, rdx
	jnl get.endMatching

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.firstMatch
	mov r8, [rbx]
	bt r8, 0b					; Match firstMatch
	jnc get.matchEvery


	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.matchIndexCount
	mov r8, [rbx]
	mov rdx, [get.matchFoundCount]
	cmp r8, rdx					; Already reached start & end when required?
	je get.endMatching


	get.matchEvery:


	.matchingEndOrStart:

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.start
	mov r8, [rbx]
	bt r8, 0b					; Match start
	jnc get.matchEnd				; Only match end

	mov rbx, [get.startMatchFound]
	mov rcx, 1b
	cmp rcx, rbx
	je get.matchEnd

	mov rcx, 0
	mov [get.matchingEnd], rcx


	jmp get.nextContains
	get.matchEnd:

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.end
	mov r8, [rbx]
	bt r8, 0b					; Match end
	jnc get.nextContains				; Only match start


	mov rcx, 1b
	mov [get.matchingEnd], rcx


	get.nextContains:
	mov rbx, [get.containsRangeList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl get.endContains


	sub rsp, 8*8
	mov rcx, [get.containsRangeList]
	call list.getNextItem
	add rsp, 8*8
	mov [get.containsAddr], rax


	sub rsp, 8*8
	mov rcx, [get.containsAddr]
	call letters.letterLength
	add rsp, 8*8
	mov [get.containsLength], rax


	mov rcx, [get.matchingIndex]
	mov [get.containsLength], rax
	add rcx, rax
	mov rdx, [get.lettersLength]
	cmp rcx, rdx					; Lengths less than or equal
	jnle get.nextContains


	cld

	mov rdi, [get.containsAddr]
	mov rsi, [get.letters]
	mov r8, [get.matchingIndex]
	add rsi, r8
	
	mov rcx, [get.containsLength]

	repe cmpsb

	jnz get.nextMatch				; noMatch


	.matchFound:

	

	mov rdx, [get.matchingEnd]
	mov rcx, 1b
	cmp rcx, rdx
	jne get.matchingStart

	mov rbx, [get.matchingIndex]
	mov rcx, [get.containsLength]
	sub rcx, 1b
	add rbx, rcx
	mov rdx, rbx
	
	jmp get.newMatchListItem

	.matchingStart:	

	mov rdx, [get.matchingIndex]


	get.newMatchListItem:

	sub rsp, 8*8
	;mov rdx,[get.containsLength]
	mov rcx, [get.list]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [get.matchFoundCount]
	add rbx, 1b
	mov [get.matchFoundCount], rbx

	mov rbx, [get.matchFlow]
	add rbx, MatchFlow.startEndLength
	mov r8, [rbx]
	bt r8, 0b					; Match start end length
	jnc get.notMatchingStartEndLength		

	sub rsp, 8*8
	mov rbx, [get.matchingIndex]
	mov rcx, [get.containsLength]
	sub rcx, 1b
	add rbx, rcx
	mov rdx, rbx
	mov rcx, [get.list]
	call list.newLastItem
	add rsp, 8*8

	mov rbx, [get.matchFoundCount]
	add rbx, 1b
	mov [get.matchFoundCount], rbx

	mov rcx, 1b
	mov [get.startMatchFound], rcx

	.notMatchingStartEndLength:

	mov rcx, 1b
	mov r8, 0
	mov rbx, [get.startMatchFound]
	cmp rbx, rcx
	je get.clearMatchStartFound		; Either way, invert

	mov [get.startMatchFound], rcx

	jmp get.increaseMatchingIndex
	.clearMatchStartFound:

	mov [get.startMatchFound], r8


	.increaseMatchingIndex:


	mov rbx, [get.matchingIndex]
	mov rcx, [get.containsLength]
	add rbx, rcx
	mov [get.matchingIndex], rbx		; Increase by 1 when no match, containsLength when match

	jmp get.resetContains


	get.endContains:

	mov rbx, [get.matchingIndex]
	mov rcx, 1b
	add rbx, rcx
	mov [get.matchingIndex], rbx		; Increase by 1 when no match, containsLength when match

	get.resetContains:
	

	sub rsp, 8*8
	mov rcx, [get.containsRangeList]
	call list.resetIndex
	add rsp, 8*8


	jmp get.nextMatch





	get.endMatching:

	sub rsp, 8*8
	mov r8, [get.matchFlow]
	mov rdx, 0
	mov rcx, [get.heapAddress]
	call [HeapFree]
	add rsp, 8*8

	mov rax, [get.list]


	get.end:


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

; Returns match results with 0 items when letters not same
; Returns greater than 0 items in List results when match

matching.lettersSame:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lettersSame.heapAddress qword at rbp-8  
	label lettersSame.handleAllocatedMemory qword at rbp-16
	label lettersSame.matchFlow qword at rbp-24 
	label lettersSame.list qword at rbp-32
	label lettersSame.matches qword at rbp-40
	label lettersSame.letters qword at rbp-48
	label lettersSame.containsRangeList qword at rbp-56
	label lettersSame.containsAddr qword at rbp-64
	label lettersSame.matchingIndex qword at rbp-72
	label lettersSame.containLetters qword at rbp-80
	label lettersSame.startMatchFound qword at rbp-88
	label lettersSame.matchFoundCount qword at rbp-96
	label lettersSame.lettersLength qword at rbp-104
	label lettersSame.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersSame.letters], rcx
	mov [lettersSame.containLetters], rdx


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
	call new
	add rsp, 8*8
	mov [lettersSame.matches], rax

	mov rbx, [lettersSame.matches]
	add rbx, Matches.flags
	mov r8, 10001b
	mov [rbx], r8

	mov rbx, [lettersSame.matches]
	add rbx, Matches.transformFlags
	mov r8, 100b
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [lettersSame.containLetters]
	mov rbx, [lettersSame.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersSame.letters]
	mov rcx, [lettersSame.matches]
	call get
	add rsp, 8*8
	mov rax, rax


	lettersSame.end:


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


; Returns match results with 0 items when letters not same, and not same lengths
; Returns greater than 0 items in List results when match

matching.lettersSameExact:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label lettersSameExact.heapAddress qword at rbp-8  
	label lettersSameExact.handleAllocatedMemory qword at rbp-16
	label lettersSameExact.matchFlow qword at rbp-24 
	label lettersSameExact.list qword at rbp-32
	label lettersSameExact.matches qword at rbp-40
	label lettersSameExact.letters qword at rbp-48
	label lettersSameExact.containsRangeList qword at rbp-56
	label lettersSameExact.containsAddr qword at rbp-64
	label lettersSameExact.matchingIndex qword at rbp-72
	label lettersSameExact.containLetters qword at rbp-80
	label lettersSameExact.length1 qword at rbp-88
	label lettersSameExact.length2 qword at rbp-96
	label lettersSameExact.lettersLength qword at rbp-104
	label lettersSameExact.matchingEnd qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [lettersSameExact.letters], rcx
	mov [lettersSameExact.containLetters], rdx


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
	mov rcx, [lettersSameExact.letters]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersSameExact.length1], rax

	sub rsp, 8*8
	mov rcx, [lettersSameExact.containLetters]
	call letters.letterLength
	add rsp, 8*8
	mov [lettersSameExact.length2], rax

	
	mov rcx, [lettersSameExact.length1]
	mov rdx, [lettersSameExact.length2]
	cmp rcx, rdx
	je lettersSameExact.sameLength

	sub rsp, 8*8
	call list.new
	add rsp, 8*8


	jmp lettersSameExact.end


	.sameLength:


	sub rsp, 8*8
	call new
	add rsp, 8*8
	mov [lettersSameExact.matches], rax

	mov rbx, [lettersSameExact.matches]
	add rbx, Matches.flags
	mov r8, 10001b
	mov [rbx], r8

	mov rbx, [lettersSameExact.matches]
	add rbx, Matches.transformFlags
	mov r8, 100b
	mov [rbx], r8

	sub rsp, 8*8
	mov rdx, [lettersSameExact.containLetters]
	mov rbx, [lettersSameExact.matches]
	add rbx, Matches.containsRangeList
	mov rcx, [rbx]
	call list.newLastItem
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [lettersSameExact.letters]
	mov rcx, [lettersSameExact.matches]
	call get
	add rsp, 8*8
	mov rax, rax


	lettersSameExact.end:


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