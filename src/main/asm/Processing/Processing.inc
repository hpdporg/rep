


section '.data' data readable writeable align 16







	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM


section '.text' code readable writeable executable align 16

;handle reservedword (parsing must categorize these flags)

processing:
namespace processing
processing.processRep:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*13);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processRep.heapAddress qword at rbp-8  
	label processRep.handleAllocatedMemory qword at rbp-16
	label processRep.parsing qword at rbp-24 
	label processRep.matchIndex qword at rbp-32
	label processRep.newRef qword at rbp-40
	label processRep.letters qword at rbp-48
	label processRep.nextNewlineIndex qword at rbp-56
	label processRep.parsedLetters qword at rbp-64
	label processRep.lettersIndex qword at rbp-72
	label processRep.refRegistry qword at rbp-80
	label processRep.newLineLetterLength qword at rbp-88
	label processRep.matchingStartIndex qword at rbp-96
	label processRep.nextRef qword at rbp-104
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processRep.parsing], rcx
	mov [processRep.letters], rdx	
	mov [processRep.refRegistry], r8

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
	mov r8, [processRep.refRegistry]
	mov rdx, [processRep.nextRef]
	mov rcx, [processRep.parsing]
	call processRefValues
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [processRep.refRegistry]
	mov rdx, [processRep.nextRef]
	mov rcx, [processRep.parsing]
	call processDefinedRefs
	add rsp, 8*8

	;refvalues	only when unprocessed
		;getUnprocessedParams
		;letters
		;appending
		;defineAsProcessed
		;replaceletterslist?
	;definedRefs	only when unprocessed
		;storefile	; param as list?
			;getUnprocessedParams
			;listAsVal
			;defineAsProcessed
		;retrievefile
			;getUnprocessedParams
			;listAsVal
			;defineAsProcessed

	


	.end:

	;dbgmov rax,0;[processRep.parsedLetters]



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


processing.processRefValues:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processRefValues.heapAddress qword at rbp-8  
	label processRefValues.handleAllocatedMemory qword at rbp-16
	label processRefValues.parsing qword at rbp-24 
	label processRefValues.matchIndex qword at rbp-32
	label processRefValues.newRef qword at rbp-40
	label processRefValues.letters qword at rbp-48
	label processRefValues.unprocessedParamCount qword at rbp-56
	label processRefValues.parsingRefsList qword at rbp-64
	label processRefValues.prevItem qword at rbp-72
	label processRefValues.refRegistry qword at rbp-80
	label processRefValues.item qword at rbp-88
	label processRefValues.prevItemNesting qword at rbp-96
	label processRefValues.nextRef qword at rbp-104
	label processRefValues.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processRefValues.parsing], rcx
	mov [processRefValues.nextRef], rdx	
	mov [processRefValues.refRegistry], r8

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
	mov [processRefValues.prevItem], rcx			; Begin as 0
	mov [processRefValues.item], rcx			; Begin as 0
	mov [processRefValues.prevItemNesting], rcx
	mov [processRefValues.nesting], rcx
	mov [processRefValues.unprocessedParamCount], rcx

	mov rbx, [processRefValues.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [processRefValues.parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processRefValues.parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:
	mov rbx, [processRefValues.parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl processRefValues.endParsingRefsList


	
	sub rsp, 8*8
	mov rcx, [processRefValues.parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	mov [processRefValues.item], rax


	mov rbx, [processRefValues.item]
	add rbx, Ref.flags
	mov r8, [rbx]
	mov rdx, 1b						; REF_VALUE
	cmp r8, rdx
	jne processRefValues.nextRefItem			; Skip when not REF_VALUE

	sub rsp, 8*8
	mov rcx, [processRefValues.item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [processRefValues.unprocessedParamCount], rax
	cmp rax, 0
	jne processRefValues.hasUnprocessedParams		; Process when any params are unprocessed (param count may have increased: reprocessed)

	mov rbx, [processRefValues.item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne processRefValues.nextRefItem			; Skip when already processed (not unprocessed)

	.hasUnprocessedParams:					; More params (appending) may be needed with further processing

	sub rsp, 8*8
	mov r8, [processRefValues.refRegistry]
	mov rdx, [processRefValues.nextRef]
	mov rcx, [processRefValues.parsing]
	call processLetters
	add rsp, 8*8


	sub rsp, 8*8
	mov r8, [processRefValues.refRegistry]
	mov rdx, [processRefValues.nextRef]
	mov rcx, [processRefValues.parsing]
	call processAppending
	add rsp, 8*8


	jmp processRefValues.nextRefItem
	.endParsingRefsList:


	.end:
	mov rax, [processRefValues.nextRef]


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

processing.processDefinedRefs:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processDefinedRefs.heapAddress qword at rbp-8  
	label processDefinedRefs.handleAllocatedMemory qword at rbp-16
	label processDefinedRefs.parsing qword at rbp-24 
	label processDefinedRefs.matchIndex qword at rbp-32
	label processDefinedRefs.newRef qword at rbp-40
	label processDefinedRefs.letters qword at rbp-48
	label processDefinedRefs.nextNewlineIndex qword at rbp-56
	label processDefinedRefs.parsingRefsList qword at rbp-64
	label processDefinedRefs.prevItem qword at rbp-72
	label processDefinedRefs.refRegistry qword at rbp-80
	label processDefinedRefs.item qword at rbp-88
	label processDefinedRefs.prevItemNesting qword at rbp-96
	label processDefinedRefs.nextRef qword at rbp-104
	label processDefinedRefs.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processDefinedRefs.parsing], rcx
	mov [processDefinedRefs.nextRef], rdx	
	mov [processDefinedRefs.refRegistry], r8

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
	mov [processDefinedRefs.prevItem], rcx			; Begin as 0
	mov [processDefinedRefs.item], rcx			; Begin as 0
	mov [processDefinedRefs.prevItemNesting], rcx
	mov [processDefinedRefs.nesting], rcx

	mov rbx, [processDefinedRefs.parsing]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [processDefinedRefs.parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processDefinedRefs.parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:
	mov rbx, [processDefinedRefs.parsingRefsList]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl processDefinedRefs.endParsingRefsList


	
	sub rsp, 8*8
	mov rcx, [processDefinedRefs.parsingRefsList]
	call [getNextItem]
	add rsp, 8*8
	mov [processDefinedRefs.item], rax


	mov rbx, [processDefinedRefs.item]
	add rbx, Ref.flags
	mov r8, [rbx]
	mov rdx, 100b
	cmp r8, rdx
	jne processDefinedRefs.nextRefItem			; Skip when not REF_DEFINED


	sub rsp, 8*8
	mov rcx, [processDefinedRefs.item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [processDefinedRefs.unprocessedParamCount], rax
	cmp rax, 0
	jne processDefinedRefs.hasUnprocessedParams		; Process when any params are unprocessed. Should not matter with defined refs, but maybe will with future changes.

	mov rbx, [processDefinedRefs.item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne processDefinedRefs.nextRefItem			; Skip when already processed (not unprocessed)

	.hasUnprocessedParams:					; More params (appending) may be needed with further processing

	sub rsp, 8*8
	mov r8, [processDefinedRefs.refRegistry]
	mov rdx, [processDefinedRefs.nextRef]
	mov rcx, [processDefinedRefs.parsing]
	call processStoreFile
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [processDefinedRefs.refRegistry]
	mov rdx, [processDefinedRefs.nextRef]
	mov rcx, [processDefinedRefs.parsing]
	;call processRetrieveFile
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [processDefinedRefs.refRegistry]
	mov rdx, [processDefinedRefs.nextRef]
	mov rcx, [processDefinedRefs.parsing]
	;call processReplaceLettersList
	add rsp, 8*8



	jmp processDefinedRefs.nextRefItem
	.endParsingRefsList:


	.end:
	mov rax, [processDefinedRefs.nextRef]


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

processing.getUnprocessedParams:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getUnprocessedParams.heapAddress qword at rbp-8  
	label getUnprocessedParams.handleAllocatedMemory qword at rbp-16
	label getUnprocessedParams.parsing qword at rbp-24 
	label getUnprocessedParams.unprocessedCount qword at rbp-32
	label getUnprocessedParams.list qword at rbp-40
	label getUnprocessedParams.letters qword at rbp-48
	label getUnprocessedParams.nextNewlineIndex qword at rbp-56
	label getUnprocessedParams.parsingRefsList qword at rbp-64
	label getUnprocessedParams.prevItem qword at rbp-72
	label getUnprocessedParams.refRegistry qword at rbp-80
	label getUnprocessedParams.item qword at rbp-88
	label getUnprocessedParams.prevItemNesting qword at rbp-96
	label getUnprocessedParams.nextRef qword at rbp-104
	label getUnprocessedParams.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getUnprocessedParams.item], rcx


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
	mov [getUnprocessedParams.unprocessedCount], rcx			; Begin as 0



	mov rbx, [getUnprocessedParams.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [getUnprocessedParams.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [getUnprocessedParams.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:
	mov rbx, [getUnprocessedParams.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl getUnprocessedParams.endItemList


	
	sub rsp, 8*8
	mov rcx, [getUnprocessedParams.list]
	call [getNextItem]
	add rsp, 8*8
	mov [getUnprocessedParams.item], rax


	mov rbx, [getUnprocessedParams.item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne getUnprocessedParams.nextRefItem			; Skip when already processed (not unprocessed)

	mov rcx, [getUnprocessedParams.unprocessedCount]
	add rcx, 1b
	mov [getUnprocessedParams.unprocessedCount], rcx	; Increment when unprocessed


	jmp getUnprocessedParams.nextRefItem
	.endItemList:


	.end:
	mov rax, [getUnprocessedParams.unprocessedCount]


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

processing.processLetters:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processLetters.heapAddress qword at rbp-8  
	label processLetters.handleAllocatedMemory qword at rbp-16
	label processLetters.parsing qword at rbp-24 
	label processLetters.unprocessedCount qword at rbp-32
	label processLetters.newRef qword at rbp-40
	label processLetters.letters qword at rbp-48
	label processLetters.nextNewlineIndex qword at rbp-56
	label processLetters.list qword at rbp-64
	label processLetters.prevItem qword at rbp-72
	label processLetters.refRegistry qword at rbp-80
	label processLetters.item qword at rbp-88
	label processLetters.unprocessedParamCount qword at rbp-96
	label processLetters.nextRef qword at rbp-104
	label processLetters.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processLetters.parsing], rcx
	mov [processLetters.item], rdx	
	mov [processLetters.refRegistry], r8

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
	mov [processLetters.unprocessedParamCount], rcx			; Begin as 0


	sub rsp, 8*8
	mov rcx, [processLetters.item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [processLetters.unprocessedParamCount], rax


	mov rbx, [processLetters.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processLetters.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processLetters.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:
	mov rbx, [processLetters.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl processLetters.endItemList


	
	sub rsp, 8*8
	mov rcx, [processLetters.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processLetters.nextRef], rax

	mov rbx, [processLetters.list]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 1b
	jne processLetters.notFirstIndex
	
	.firstParam:
	mov rbx, [processLetters.nextRef]
	add rbx, Ref.definedRefFlags
	mov rcx, [rbx]
	mov rdx, 100b					; DEFINED_REF_LETTERS
	cmp rcx, rdx
	jne processLetters.end				; Not Letters
	
	mov rbx, [processLetters.nextRef]
	add rbx, Ref.paramCount
	mov r8, [rbx]
	mov rbx, [processLetters.list]
	add rbx, List.itemsCount
	mov rcx, [rbx]
	sub rcx, 1b
	cmp rcx, r8
	jne processLetters.end				; Do not have sufficient params yet
	mov r8, [processLetters.unprocessedParamCount]
	cmp r8, 0
	jne processLetters.nextRefItem			; Continue processing

	sub rsp, 8*8
	mov rcx, [processLetters.item]
	call defineAsProcessed				; Done, letters was not marked as processed, should not occur
	add rsp, 8*8

	jmp processLetters.endItemList
	.notFirstIndex:

	sub rsp, 8*8
	mov rbx, [processLetters.nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [letterLength]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx,rax
	call [linearAllocate]
	add rsp, 8*8

	mov rbx, [processLetters.item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax

	sub rsp, 8*8
	mov rcx, [processLetters.item]
	call defineAsProcessed				; Done
	add rsp, 8*8
	jmp processLetters.endItemList


	jmp processLetters.nextRefItem
	.endItemList:


	.end:
	mov rax, [processLetters.nextRef]


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

processing.processAppending:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processAppending.heapAddress qword at rbp-8  
	label processAppending.handleAllocatedMemory qword at rbp-16
	label processAppending.parsing qword at rbp-24 
	label processAppending.unprocessedCount qword at rbp-32
	label processAppending.newRef qword at rbp-40
	label processAppending.letters qword at rbp-48
	label processAppending.processedCount qword at rbp-56
	label processAppending.list qword at rbp-64
	label processAppending.prevItem qword at rbp-72
	label processAppending.refRegistry qword at rbp-80
	label processAppending.item qword at rbp-88
	label processAppending.unprocessedParamCount qword at rbp-96
	label processAppending.nextRef qword at rbp-104
	label processAppending.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processAppending.parsing], rcx
	mov [processAppending.item], rdx	
	mov [processAppending.refRegistry], r8

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
	mov [processAppending.unprocessedParamCount], rcx			; Begin as 0
	mov [processAppending.processedCount], rcx

	sub rsp, 8*8
	mov rcx, [processAppending.item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [processAppending.unprocessedParamCount], rax


	mov rbx, [processAppending.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processAppending.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processAppending.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:
	mov rbx, [processAppending.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl processAppending.endItemList


	
	sub rsp, 8*8
	mov rcx, [processAppending.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processAppending.nextRef], rax

	mov rbx, [processAppending.list]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 1b
	jne processAppending.notFirstIndex
	
	.firstParam:
	mov rbx, [processAppending.nextRef]
	add rbx, Ref.definedRefFlags
	mov rcx, [rbx]
	mov rdx, 0b					; (Undefined, not DEFINED_REF_LETTERS)
	cmp rcx, rdx
	jne processAppending.end			; Is Letters, not appending. Base item must be ref value also.
	

	sub rsp, 8*8
	mov rcx, [processAppending.nextRef]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	mov [processAppending.nextRef], rax
	add rax, Ref.unprocessed
	mov rcx, [rax]
	cmp rcx, 1b
	je processAppending.endItemList			; Param refs not ready yet

	sub rsp, 8*8
	mov rbx, [processAppending.nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	mov rbx, [processAppending.item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax

	mov r8, [processAppending.processedCount]
	add r8, 1b					; Increment
	mov [processAppending.processedCount], r8

	jmp processAppending.nextRefItem
	
	.notFirstIndex:

	sub rsp, 8*8
	mov rcx, [processAppending.nextRef]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	mov [processAppending.nextRef], rax
	add rax, Ref.unprocessed
	mov rcx, [rax]
	cmp rcx, 1b
	je processAppending.endItemList			; Param refs not ready yet

	sub rsp, 8*8
	mov rbx, [processAppending.nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rdx,rax
	mov rbx, [processAppending.item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [appendLetters]				; Append
	add rsp, 8*8

	mov rbx, [processAppending.item]
	add rbx, Ref.valueAlloc				; Allocation goes in item Ref's value alloc
	mov [rbx], rax

	mov r8, [processAppending.processedCount]
	add r8, 1b					; Increment
	mov [processAppending.processedCount], r8




	jmp processAppending.nextRefItem
	.endItemList:



	mov rbx, [processAppending.list]
	add rbx, List.itemsCount
	mov r9, [processAppending.processedCount]
	mov rcx, [rbx]
	cmp rcx, r9
	jne processAppending.notReady

	sub rsp, 8*8
	mov rcx, [processAppending.item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	.notReady:


	.end:
	mov rax, [processAppending.nextRef]


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




processing.processStoreFile:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processStoreFile.heapAddress qword at rbp-8  
	label processStoreFile.handleAllocatedMemory qword at rbp-16
	label processStoreFile.parsing qword at rbp-24 
	label processStoreFile.unprocessedCount qword at rbp-32
	label processStoreFile.newRef qword at rbp-40
	label processStoreFile.letters qword at rbp-48
	label processStoreFile.processedCount qword at rbp-56
	label processStoreFile.list qword at rbp-64
	label processStoreFile.prevItem qword at rbp-72
	label processStoreFile.refRegistry qword at rbp-80
	label processStoreFile.item qword at rbp-88
	label processStoreFile.unprocessedParamCount qword at rbp-96
	label processStoreFile.nextRef qword at rbp-104
	label processStoreFile.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processStoreFile.parsing], rcx
	mov [processStoreFile.item], rdx	
	mov [processStoreFile.refRegistry], r8

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
	mov [processStoreFile.unprocessedParamCount], rcx			; Begin as 0
	mov [processStoreFile.processedCount], rcx

	sub rsp, 8*8
	mov rcx, [processStoreFile.item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [processStoreFile.unprocessedParamCount], rax


	mov rbx, [processStoreFile.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processStoreFile.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processStoreFile.list]
	call [resetIndex]
	add rsp, 8*8


	mov rbx, [processStoreFile.item]
	add rbx, Ref.definedRefFlags
	mov rcx, [rbx]
	mov rdx, 1b					; DEFINED_REF_STORE_FILE
	cmp rcx, rdx
	jne processStoreFile.end			; Is not DEFINED_REF_STORE_FILE
	




	.nextRefItem:
	mov rbx, [processStoreFile.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl processStoreFile.endItemList


	
	sub rsp, 8*8
	mov rcx, [processStoreFile.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processStoreFile.nextRef], rax

	mov rbx, [processStoreFile.list]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 1b
	jne processStoreFile.notFirstIndex
	
	.firstParam:	; this should be ref itself
	mov rbx, [processStoreFile.nextRef]
	add rbx, Ref.definedRefFlags
	mov rcx, [rbx]
	mov rdx, 100b					; DEFINED_REF_LETTERS
	cmp rcx, rdx
	je processStoreFile.end				; Is Letters, not appending
	

	sub rsp, 8*8
	mov rcx, [processStoreFile.nextRef]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	mov [processStoreFile.nextRef], rax
	add rax, Ref.unprocessed
	mov rcx, [rax]
	cmp rcx, 1b
	je processStoreFile.endItemList			; Param refs not ready yet

	sub rsp, 8*8
	mov rbx, [processStoreFile.nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	mov rbx, [processStoreFile.item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax

	mov r8, [processStoreFile.processedCount]
	add r8, 1b					; Increment
	mov [processStoreFile.processedCount], r8

	jmp processStoreFile.nextRefItem
	
	.notFirstIndex:

	sub rsp, 8*8
	mov rcx, [processStoreFile.nextRef]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	mov [processStoreFile.nextRef], rax
	add rax, Ref.unprocessed
	mov rcx, [rax]
	cmp rcx, 1b
	je processStoreFile.endItemList			; Param refs not ready yet

	sub rsp, 8*8
	mov rbx, [processStoreFile.nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rdx,rax
	mov rbx, [processStoreFile.item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [appendLetters]				; Append
	add rsp, 8*8

	mov rbx, [processStoreFile.item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax

	mov r8, [processStoreFile.processedCount]
	add r8, 1b					; Increment
	mov [processStoreFile.processedCount], r8




	jmp processStoreFile.nextRefItem
	.endItemList:



	mov rbx, [processStoreFile.list]
	add rbx, List.itemsCount
	mov r9, [processStoreFile.processedCount]
	mov rcx, [rbx]
	cmp rcx, r9
	jne processStoreFile.notReady

	sub rsp, 8*8
	mov rcx, [processStoreFile.item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	.notReady:


	.end:
	mov rax, [processStoreFile.nextRef]


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

processing.defineAsProcessed:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label defineAsProcessed.heapAddress qword at rbp-8  
	label defineAsProcessed.handleAllocatedMemory qword at rbp-16
	label defineAsProcessed.parsing qword at rbp-24 
	label defineAsProcessed.unprocessedCount qword at rbp-32
	label defineAsProcessed.newRef qword at rbp-40
	label defineAsProcessed.letters qword at rbp-48
	label defineAsProcessed.nextNewlineIndex qword at rbp-56
	label defineAsProcessed.list qword at rbp-64
	label defineAsProcessed.prevItem qword at rbp-72
	label defineAsProcessed.refRegistry qword at rbp-80
	label defineAsProcessed.item qword at rbp-88
	label defineAsProcessed.unprocessedParamCount qword at rbp-96
	label defineAsProcessed.nextRef qword at rbp-104
	label defineAsProcessed.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [defineAsProcessed.item], rcx
	

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

	



	mov rbx, [defineAsProcessed.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [defineAsProcessed.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [defineAsProcessed.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:
	mov rbx, [defineAsProcessed.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl defineAsProcessed.endItemList


	
	sub rsp, 8*8
	mov rcx, [defineAsProcessed.list]
	call [getNextItem]
	add rsp, 8*8
	mov [defineAsProcessed.nextRef], rax

	

	mov rbx, [defineAsProcessed.nextRef]
	add rbx, Ref.unprocessed
	mov rcx, 0					; Param as processed
	mov [rbx], rcx


	jmp defineAsProcessed.nextRefItem
	.endItemList:

	mov rbx, [defineAsProcessed.item]
	add rbx, Ref.unprocessed
	mov rcx, 0				; Ref as processed
	mov [rbx], rcx


	.end:
	mov rax, [defineAsProcessed.nextRef]


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

; processRefItem
	; is ref the defined ref or not that must be processed, skip otherwise
	; is the param count sufficient, skip otherwise
	; are the params unprocessed, skip otherwise
		; processLetters
		; processAppending
	; define items and params as unprocessed

processing.processRefItem:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processRefItem.heapAddress qword at rbp-8  
	label processRefItem.handleAllocatedMemory qword at rbp-16
	label processRefItem.definedRefFlags qword at rbp-24 
	label processRefItem.unprocessedCount qword at rbp-32
	label processRefItem.newRef qword at rbp-40
	label processRefItem.definedItemIndex qword at rbp-48
	label processRefItem.nextNewlineIndex qword at rbp-56
	label processRefItem.list qword at rbp-64
	label processRefItem.prevItem qword at rbp-72
	label processRefItem.refRegistry qword at rbp-80
	label processRefItem.item qword at rbp-88
	label processRefItem.unprocessedParamCount qword at rbp-96
	label processRefItem.nextRef qword at rbp-104
	label processRefItem.nesting qword at rbp-112
	label processRefItem.minParamCount qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processRefItem.item], rcx
	mov [processRefItem.minParamCount], rdx	
	mov [processRefItem.refBaseFlags], r8			; 
	mov [processRefItem.definedRefFlags], r9		; Defined Ref flags

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
	mov rcx, [processRefItem.item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [processRefItem.unprocessedParamCount], rax
	cmp rax, 0
	jne processRefItem.hasUnprocessedParams			; Can process

	mov rbx, [processRefItem.item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne processRefItem.end					; Item itself also processed. No need to process


	.hasUnprocessedParams:

	
	mov r8, [processRefItem.refBaseFlags]
	mov rcx, 1b						; REF_BASE_DEFINED_REF_FIRST_PARAM
	cmp r8, rcx
	jne processRefItem.baseNotFirst


	; letters


	.baseNotFirst:
	mov rcx, 10b						; REF_BASE_ITEM_DEFINED_RE
	cmp r8, rcx
	jne processRefItem.baseNotItem

	; storefile retrievefile



	.baseNotItem:
	mov rcx, 100b						; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM
	cmp r8, rcx
	jne processRefItem.end					; Handle other cases later


	; appending







	; each process should return count
	mov [processRefItem.processedCount], rax



	
	mov rbx, [processRefItem.list]
	add rbx, List.itemsCount
	mov r9, [processRefItem.processedCount]
	mov rcx, [rbx]
	cmp rcx, r9
	jne processRefItem.notReady

	sub rsp, 8*8
	mov rcx, [processRefItem.item]
	call defineAsProcessed					; Done, refs processed
	add rsp, 8*8


	.notReady:




	.end:
	mov rax, [processRefItem.nextRef]


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