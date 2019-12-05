


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


	;definedRefFlags
	;DEFINED_REF_SEPARATOR	DEFINED_REF_REPLACE_LETTERS_LIST	DEFINED_REF_LETTERS	DEFINED_REF_RETRIEVE_FILE	DEFINED_REF_STORE_FILE


	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM

	; letters
	sub rsp, 8*8
	mov r11, [processRefValues.refRegistry]
	mov qword [rsp+5*8], r11
	mov r10, [processRefValues.parsing]
	mov qword [rsp+4*8], r10
	mov r9, 100b						; definedRefFlags	DEFINED_REF_LETTERS
	mov r8,	1b						; refBaseFlags		REF_BASE_DEFINED_REF_FIRST_PARAM
	mov rdx, 10b						; minParamCount
	mov rcx, [processRefValues.nextRef]
	call processRefItem
	add rsp, 8*8

	; appending
	sub rsp, 8*8
	mov r11, [processRefValues.refRegistry]
	mov qword [rsp+5*8], r11
	mov r10, [processRefValues.parsing]
	mov qword [rsp+4*8], r10
	mov r9, 0						; definedRefFlags	No defined ref
	mov r8,	100b						; refBaseFlags		REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM
	mov rdx, 1b 						; minParamCount	
	mov rcx, [processRefValues.nextRef]
	call processRefItem
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
	sub rsp, (8*15);+(8*6)

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
	label processDefinedRefs.unprocessedParamCount qword at rbp-120

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


	;definedRefFlags
	;DEFINED_REF_SEPARATOR	DEFINED_REF_REPLACE_LETTERS_LIST	DEFINED_REF_LETTERS	DEFINED_REF_RETRIEVE_FILE	DEFINED_REF_STORE_FILE


	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM



	; processStoreFile
	sub rsp, 8*8
	mov r11, [processDefinedRefs.refRegistry]
	mov qword [rsp+5*8], r11
	mov r10, [processDefinedRefs.parsing]
	mov qword [rsp+4*8], r10
	mov r9, 1b						; definedRefFlags	DEFINED_REF_STORE_FILE
	mov r8,	10b						; refBaseFlags		REF_BASE_ITEM_DEFINED_REF
	mov rdx, 10b						; minParamCount
	mov rcx, [processDefinedRefs.nextRef]
	call processRefItem
	add rsp, 8*8

	; processRetrieveFile
	sub rsp, 8*8
	mov r11, [processDefinedRefs.refRegistry]
	mov qword [rsp+5*8], r11
	mov r10, [processDefinedRefs.parsing]
	mov qword [rsp+4*8], r10
	mov r9, 10b						; definedRefFlags	DEFINED_REF_RETRIEVE_FILE
	mov r8,	10b						; refBaseFlags		REF_BASE_ITEM_DEFINED_REF
	mov rdx, 1b 						; minParamCount	
	mov rcx, [processDefinedRefs.nextRef]
	call processRefItem
	add rsp, 8*8



	; processReplaceLettersList
	sub rsp, 8*8
	mov r11, [processDefinedRefs.refRegistry]
	mov qword [rsp+5*8], r11
	mov r10, [processDefinedRefs.parsing]
	mov qword [rsp+4*8], r10
	mov r9, 1000b						; definedRefFlags	DEFINED_REF_REPLACE_LETTERS_LIST
	mov r8,	1b						; refBaseFlags		REF_BASE_DEFINED_REF_FIRST_PARAM
	mov rdx, 100b 						; minParamCount	
	mov rcx, [processDefinedRefs.nextRef]
	call processRefItem
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

processing.getUnprocessedRegisteredParams:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getUnprocessedRegisteredParams.heapAddress qword at rbp-8  
	label getUnprocessedRegisteredParams.handleAllocatedMemory qword at rbp-16
	label getUnprocessedRegisteredParams.parsing qword at rbp-24 
	label getUnprocessedRegisteredParams.unprocessedCount qword at rbp-32
	label getUnprocessedRegisteredParams.list qword at rbp-40
	label getUnprocessedRegisteredParams.letters qword at rbp-48
	label getUnprocessedRegisteredParams.nextNewlineIndex qword at rbp-56
	label getUnprocessedRegisteredParams.parsingRefsList qword at rbp-64
	label getUnprocessedRegisteredParams.prevItem qword at rbp-72
	label getUnprocessedRegisteredParams.refRegistry qword at rbp-80
	label getUnprocessedRegisteredParams.item qword at rbp-88
	label getUnprocessedRegisteredParams.prevItemNesting qword at rbp-96
	label getUnprocessedRegisteredParams.nextRef qword at rbp-104
	label getUnprocessedRegisteredParams.nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getUnprocessedRegisteredParams.item], rcx
	mov [getUnprocessedRegisteredParams.refRegistry], rdx


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
	mov [getUnprocessedRegisteredParams.unprocessedCount], rcx			; Begin as 0



	mov rbx, [getUnprocessedRegisteredParams.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [getUnprocessedRegisteredParams.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [getUnprocessedRegisteredParams.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:
	mov rbx, [getUnprocessedRegisteredParams.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl getUnprocessedRegisteredParams.endItemList


	
	sub rsp, 8*8
	mov rcx, [getUnprocessedRegisteredParams.list]
	call [getNextItem]
	add rsp, 8*8
	mov [getUnprocessedRegisteredParams.nextRef], rax

	sub rsp, 8*8
	mov r8, 0
	mov rbx, [getUnprocessedRegisteredParams.nextRef]
	add rbx, Ref.ref
	mov rdx, [rbx]
	mov rcx, [getUnprocessedRegisteredParams.refRegistry]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	mov [getUnprocessedRegisteredParams.nextRef], rax
	cmp rax, 0
	je getUnprocessedRegisteredParams.nextRefItem
	add rax, Ref.unprocessed
	mov rcx, [rax]
	mov rdx, 1b
	cmp rcx, rdx
	jne getUnprocessedRegisteredParams.nextRefItem			; Skip when already processed (not unprocessed)

	mov rcx, [getUnprocessedRegisteredParams.unprocessedCount]
	add rcx, 1b
	mov [getUnprocessedRegisteredParams.unprocessedCount], rcx	; Increment when unprocessed


	jmp getUnprocessedRegisteredParams.nextRefItem
	.endItemList:


	.end:
	mov rax, [getUnprocessedRegisteredParams.unprocessedCount]


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
	sub rsp, (8*15);+(8*6)

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
	label processLetters.definedRefFlags qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processLetters.parsing], rcx
	mov [processLetters.item], rdx	
	mov [processLetters.refRegistry], r8
	mov [processLetters.definedRefFlags], r9

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

	


	mov rcx, [processLetters.definedRefFlags]
	mov r9, 100b						; definedRefFlags	DEFINED_REF_LETTERS
	cmp rcx, r9 
	jne processLetters.end					; Only attempt processing letters



	mov rbx, [processLetters.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processLetters.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processLetters.list]
	call [resetIndex]
	add rsp, 8*8


	mov rbx, [processLetters.list]
	add rbx, List.index
	mov rcx, 1b
	mov [rbx], rcx				; Param after lettersRef


	.nextRefItem:				; Just ensure end is not reached
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


	sub rsp, 8*8
	mov rbx, [processLetters.nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [copyLetters]				
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
	sub rsp, (8*15);+(8*6)

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
	label processAppending.definedRefFlags qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processAppending.parsing], rcx
	mov [processAppending.item], rdx	
	mov [processAppending.refRegistry], r8
	mov [processAppending.definedRefFlags], r9

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

	

	

	mov rcx, [processAppending.definedRefFlags]
	mov r9, 0b						; definedRefFlags	None
	cmp rcx, r9 
	jne processAppending.end				; Only attempt processing letters

	sub rsp, 8*8
	mov rdx, [processAppending.refRegistry]
	mov rcx, [processAppending.item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 0
	jne processAppending.end				; Appending depends on param registeredRefs being processed, not just the param

	

	mov rbx, [processAppending.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processAppending.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processAppending.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:						; Ensure end is not reached
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

	sub rsp, 8*8
	mov rbx, [processAppending.nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	mov rbx, [processAppending.item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax


	
	jmp processAppending.nextRefItem
	
	.notFirstIndex:

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





	jmp processAppending.nextRefItem
	.endItemList:


	sub rsp, 8*8
	mov rcx, [processAppending.item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	.notReady:


	.end:
	;mov rax, [processAppending.nextRef]


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
	sub rsp, (8*16);+(8*6)

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
	label processStoreFile.definedRefFlags qword at rbp-120
	label processStoreFile.record qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processStoreFile.parsing], rcx
	mov [processStoreFile.item], rdx	
	mov [processStoreFile.refRegistry], r8
	mov [processStoreFile.definedRefFlags], r9

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

	


	mov rcx, [processStoreFile.definedRefFlags]
	mov r9, 1b						; definedRefFlags	DEFINED_REF_STORE_FILE
	cmp rcx, r9 
	jne processStoreFile.end				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [processStoreFile.refRegistry]
	mov rcx, [processStoreFile.item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 0
	jne processStoreFile.end				; This definedRef depends on param registeredRefs being processed, not just the param



	mov rbx, [processStoreFile.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processStoreFile.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processStoreFile.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:						; Ensure end is not reached
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


	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [processStoreFile.record], rax

	sub rsp, 8*8
	mov rcx, [processStoreFile.nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [processStoreFile.record]
	add rbx, Record.builtLocation
	mov [rbx], rax


	sub rsp, 8*8
	mov rcx, [processStoreFile.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processStoreFile.nextRef], rax


	sub rsp, 8*8
	mov rcx, [processStoreFile.nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, rax 
	mov rcx, [processStoreFile.record]
	call [storeLetters]
	add rsp, 8*8


	;jmp processStoreFile.nextRefItem
	.endItemList:


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


processing.processRetrieveFile:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processRetrieveFile.heapAddress qword at rbp-8  
	label processRetrieveFile.handleAllocatedMemory qword at rbp-16
	label processRetrieveFile.parsing qword at rbp-24 
	label processRetrieveFile.unprocessedCount qword at rbp-32
	label processRetrieveFile.newRef qword at rbp-40
	label processRetrieveFile.letters qword at rbp-48
	label processRetrieveFile.processedCount qword at rbp-56
	label processRetrieveFile.list qword at rbp-64
	label processRetrieveFile.prevItem qword at rbp-72
	label processRetrieveFile.refRegistry qword at rbp-80
	label processRetrieveFile.item qword at rbp-88
	label processRetrieveFile.unprocessedParamCount qword at rbp-96
	label processRetrieveFile.nextRef qword at rbp-104
	label processRetrieveFile.nesting qword at rbp-112
	label processRetrieveFile.definedRefFlags qword at rbp-120
	label processRetrieveFile.record qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processRetrieveFile.parsing], rcx
	mov [processRetrieveFile.item], rdx	
	mov [processRetrieveFile.refRegistry], r8
	mov [processRetrieveFile.definedRefFlags], r9

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

	


	mov rcx, [processRetrieveFile.definedRefFlags]
	mov r9, 10b						; definedRefFlags	DEFINED_REF_RETRIEVE_FILE
	cmp rcx, r9 
	jne processRetrieveFile.end				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [processRetrieveFile.refRegistry]
	mov rcx, [processRetrieveFile.item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 1b						; Second param can be unprocessed. TO-DO: improve.
	jnle processRetrieveFile.end				; This definedRef depends on param registeredRefs being processed, not just the param



	mov rbx, [processRetrieveFile.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processRetrieveFile.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processRetrieveFile.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:						; Ensure end is not reached
	mov rbx, [processRetrieveFile.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl processRetrieveFile.endItemList


	
	sub rsp, 8*8
	mov rcx, [processRetrieveFile.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processRetrieveFile.nextRef], rax


	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [processRetrieveFile.record], rax

	sub rsp, 8*8
	mov rcx, [processRetrieveFile.nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [processRetrieveFile.record]
	add rbx, Record.builtLocation
	mov [rbx], rax


	sub rsp, 8*8
	mov rcx, [processRetrieveFile.record]
	call [retrieve]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [processRetrieveFile.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processRetrieveFile.nextRef], rax



	mov rbx, [processRetrieveFile.record]
	add rbx, Record.allocAddr
	mov rdx, [processRetrieveFile.nextRef]
	add rdx, Ref.valueAlloc
	mov r8, [rbx]
	mov [rdx], r8





	;jmp processRetrieveFile.nextRefItem
	.endItemList:


	sub rsp, 8*8
	mov rcx, [processRetrieveFile.item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	.notReady:


	.end:
	mov rax, [processRetrieveFile.nextRef]


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

processing.processReplaceLettersList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*19);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processReplaceLettersList.heapAddress qword at rbp-8  
	label processReplaceLettersList.handleAllocatedMemory qword at rbp-16
	label processReplaceLettersList.parsing qword at rbp-24 
	label processReplaceLettersList.unprocessedCount qword at rbp-32
	label processReplaceLettersList.newRef qword at rbp-40
	label processReplaceLettersList.letters qword at rbp-48
	label processReplaceLettersList.processedCount qword at rbp-56
	label processReplaceLettersList.list qword at rbp-64
	label processReplaceLettersList.prevItem qword at rbp-72
	label processReplaceLettersList.refRegistry qword at rbp-80
	label processReplaceLettersList.item qword at rbp-88
	label processReplaceLettersList.unprocessedParamCount qword at rbp-96
	label processReplaceLettersList.nextRef qword at rbp-104
	label processReplaceLettersList.nesting qword at rbp-112
	label processReplaceLettersList.definedRefFlags qword at rbp-120
	label processReplaceLettersList.record qword at rbp-128
	label processReplaceLettersList.param1 qword at rbp-136
	label processReplaceLettersList.param2 qword at rbp-144
	label processReplaceLettersList.param3 qword at rbp-152

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processReplaceLettersList.parsing], rcx
	mov [processReplaceLettersList.item], rdx	
	mov [processReplaceLettersList.refRegistry], r8
	mov [processReplaceLettersList.definedRefFlags], r9

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

	


	mov rcx, [processReplaceLettersList.definedRefFlags]
	mov r9, 1000b						; definedRefFlags	DEFINED_REF_REPLACE_LETTERS_LIST
	cmp rcx, r9 
	jne processReplaceLettersList.end				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [processReplaceLettersList.refRegistry]
	mov rcx, [processReplaceLettersList.item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 10b
	jnle processReplaceLettersList.end				; Separator, replaceLettersList definedref can be unprocessed? This definedRef depends on param registeredRefs being processed, not just the param



	mov rbx, [processReplaceLettersList.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [processReplaceLettersList.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:						; Ensure end is not reached
	mov rbx, [processReplaceLettersList.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl processReplaceLettersList.endItemList


	
	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processReplaceLettersList.nextRef], rax	; replaceLettersLisst


	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processReplaceLettersList.nextRef], rax	; letters

	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.nextRef]
	call getRefLettersAlloc
	add rsp, 8*8
	mov [processReplaceLettersList.param1], rax	; letters


	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processReplaceLettersList.nextRef], rax	; list
	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.nextRef]
	call getRefLettersList
	add rsp, 8*8
	mov [processReplaceLettersList.param2], rax	; letters


	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.list]
	call [getNextItem]
	add rsp, 8*8
	mov [processReplaceLettersList.nextRef], rax	; containsLetters

	mov rbx, [processReplaceLettersList.nextRef]
	add rbx, Ref.ref
	sub rsp, 8*8
	mov rcx, [rbx]
	call [copyLetters]
	add rsp, 8*8
	mov [processReplaceLettersList.param3], rax	; containsLetters


	sub rsp, 8*8
	mov r8, [processReplaceLettersList.param3]
	mov rdx, [processReplaceLettersList.param2]
	mov rcx, [processReplaceLettersList.param1]
	call [replaceContainsLettersWithList]
	add rsp, 8*8

	mov rdx, [processReplaceLettersList.item]
	add rdx, Ref.valueAlloc
	mov [rdx], rax





	;jmp processReplaceLettersList.nextRefItem
	.endItemList:


	sub rsp, 8*8
	mov rcx, [processReplaceLettersList.item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	.notReady:


	.end:
	mov rax, [processReplaceLettersList.nextRef]


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
	sub rsp, (8*17);+(8*6)
	
	mov r10, [rsp+8*6]
	mov r11, [rsp+8*7]

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label processRefItem.heapAddress qword at rbp-8  
	label processRefItem.handleAllocatedMemory qword at rbp-16
	label processRefItem.definedRefFlags qword at rbp-24 
	label processRefItem.unprocessedCount qword at rbp-32
	label processRefItem.baseRef qword at rbp-40
	label processRefItem.definedItemIndex qword at rbp-48
	label processRefItem.nextNewlineIndex qword at rbp-56
	label processRefItem.list qword at rbp-64
	label processRefItem.parsing qword at rbp-72
	label processRefItem.refRegistry qword at rbp-80
	label processRefItem.item qword at rbp-88
	label processRefItem.unprocessedParamCount qword at rbp-96
	label processRefItem.nextRef qword at rbp-104
	label processRefItem.nesting qword at rbp-112
	label processRefItem.minParamCount qword at rbp-120
	label processRefItem.refBaseFlags qword at rbp-128
	label processRefItem.processedCount qword at rbp-136

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [processRefItem.item], rcx
	mov [processRefItem.minParamCount], rdx	
	mov [processRefItem.refBaseFlags], r8			; 
	mov [processRefItem.definedRefFlags], r9		; Defined Ref flags
	mov [processRefItem.parsing], r10
	mov [processRefItem.refRegistry], r11

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

	
	sub rsp, 8*8
	mov rdx, [processRefItem.refBaseFlags]
	mov rcx, [processRefItem.item]
	call getBaseRefUsingFlags
	add rsp, 8*8
	mov [processRefItem.baseRef], rax


	mov r8, [processRefItem.baseRef]
	add r8, Ref.definedRefFlags
	mov r10, [r8]
	mov r9, [processRefItem.definedRefFlags]
	add r9, Ref.definedRefFlags
	mov r11, [r9]
	cmp r10, r11
	jne processRefItem.end					; Not same, skip


	mov rbx, [processRefItem.item]
	add rbx, Ref.list
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	mov rcx, [processRefItem.minParamCount]
	cmp r8, rcx
	jnge processRefItem.end					; Insufficient params, skip



	sub rsp, 8*8
	mov r9, [processRefItem.definedRefFlags]
	mov r8, [processRefItem.refRegistry]
	mov rdx, [processRefItem.item]
	mov rcx, [processRefItem.parsing]
	call processLetters					
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [processRefItem.definedRefFlags]
	mov r8, [processRefItem.refRegistry]
	mov rdx, [processRefItem.item]
	mov rcx, [processRefItem.parsing]
	call processAppending				
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [processRefItem.definedRefFlags]
	mov r8, [processRefItem.refRegistry]
	mov rdx, [processRefItem.item]
	mov rcx, [processRefItem.parsing]
	call processStoreFile	
	add rsp, 8*8


	sub rsp, 8*8
	mov r9, [processRefItem.definedRefFlags]
	mov r8, [processRefItem.refRegistry]
	mov rdx, [processRefItem.item]
	mov rcx, [processRefItem.parsing]
	call processRetrieveFile			
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [processRefItem.definedRefFlags]
	mov r8, [processRefItem.refRegistry]
	mov rdx, [processRefItem.item]
	mov rcx, [processRefItem.parsing]
	call processReplaceLettersList			
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [processRefItem.item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [processRefItem.unprocessedParamCount], rax
	
	mov r9,[processRefItem.unprocessedParamCount]
	mov rcx, 0
	cmp r9, rcx
	jg processRefItem.notReady				; Still has unprocessed params

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



; item index is 0
; item's list first Ref index is 1
; Next item is last plus 1
processing.getBaseRefAtIndex:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getBaseRefAtIndex.heapAddress qword at rbp-8  
	label getBaseRefAtIndex.handleAllocatedMemory qword at rbp-16
	label getBaseRefAtIndex.parsing qword at rbp-24 
	label getBaseRefAtIndex.unprocessedCount qword at rbp-32
	label getBaseRefAtIndex.newRef qword at rbp-40
	label getBaseRefAtIndex.letters qword at rbp-48
	label getBaseRefAtIndex.nextNewlineIndex qword at rbp-56
	label getBaseRefAtIndex.list qword at rbp-64
	label getBaseRefAtIndex.prevItem qword at rbp-72
	label getBaseRefAtIndex.refRegistry qword at rbp-80
	label getBaseRefAtIndex.item qword at rbp-88
	label getBaseRefAtIndex.unprocessedParamCount qword at rbp-96
	label getBaseRefAtIndex.nextRef qword at rbp-104
	label getBaseRefAtIndex.nesting qword at rbp-112
	label getBaseRefAtIndex.index qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getBaseRefAtIndex.item], rcx
	mov [getBaseRefAtIndex.index], rdx	

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
	mov [getBaseRefAtIndex.nextRef], rcx				; Begin as 0


	mov rdx, [getBaseRefAtIndex.index]
	cmp rdx, 0
	jne getBaseRefAtIndex.useParamList

	mov rbx, [getBaseRefAtIndex.item]
	mov [getBaseRefAtIndex.nextRef], rbx
	
	jmp getBaseRefAtIndex.end





	.useParamList:


	mov rbx, [getBaseRefAtIndex.item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [getBaseRefAtIndex.list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [getBaseRefAtIndex.list]
	call [resetIndex]
	add rsp, 8*8

	mov rbx, [getBaseRefAtIndex.list]
	add rbx, List.index
	mov r8, [getBaseRefAtIndex.index]
	sub r8, 1b					; Item was included in index, so List would not include it
	mov [rbx], r8


	.nextRefItem:
	mov rbx, [getBaseRefAtIndex.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl getBaseRefAtIndex.endItemList


	
	sub rsp, 8*8
	mov rcx, [getBaseRefAtIndex.list]
	call [getNextItem]
	add rsp, 8*8
	mov [getBaseRefAtIndex.nextRef], rax


	.endItemList:	

	.end:
	mov rax, [getBaseRefAtIndex.nextRef]


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


processing.getBaseRefUsingFlags:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getBaseRefUsingFlags.heapAddress qword at rbp-8  
	label getBaseRefUsingFlags.handleAllocatedMemory qword at rbp-16
	label getBaseRefUsingFlags.parsing qword at rbp-24 
	label getBaseRefUsingFlags.unprocessedCount qword at rbp-32
	label getBaseRefUsingFlags.newRef qword at rbp-40
	label getBaseRefUsingFlags.letters qword at rbp-48
	label getBaseRefUsingFlags.nextNewlineIndex qword at rbp-56
	label getBaseRefUsingFlags.list qword at rbp-64
	label getBaseRefUsingFlags.prevItem qword at rbp-72
	label getBaseRefUsingFlags.refRegistry qword at rbp-80
	label getBaseRefUsingFlags.item qword at rbp-88
	label getBaseRefUsingFlags.unprocessedParamCount qword at rbp-96
	label getBaseRefUsingFlags.nextRef qword at rbp-104
	label getBaseRefUsingFlags.refIndex qword at rbp-112
	label getBaseRefUsingFlags.index qword at rbp-120
	label getBaseRefUsingFlags.flags qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getBaseRefUsingFlags.item], rcx
	mov [getBaseRefUsingFlags.flags], rdx	

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
	mov [getBaseRefUsingFlags.nextRef], rcx				; Begin as 0
	mov [getBaseRefUsingFlags.refIndex], rcx

	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM

	mov rcx, [getBaseRefUsingFlags.flags]
	cmp rcx, 1b
	jne getBaseRefUsingFlags.notFirst


	mov rdx, 1b
	mov [getBaseRefUsingFlags.refIndex], rdx


	jmp getBaseRefUsingFlags.getIndex
	.notFirst:

	mov rcx, [getBaseRefUsingFlags.flags]
	cmp rcx, 10b
	jne getBaseRefUsingFlags.notItem

	mov rdx, 0b
	mov [getBaseRefUsingFlags.refIndex], rdx

	jmp getBaseRefUsingFlags.getIndex
	.notItem:


	mov rcx, [getBaseRefUsingFlags.flags]
	cmp rcx, 100b
	jne getBaseRefUsingFlags.end					; Should not get here

	mov rdx, 0b
	mov [getBaseRefUsingFlags.refIndex], rdx



	.getIndex:

	sub rsp, 8*8
	mov rdx, [getBaseRefUsingFlags.refIndex]
	mov rcx, [getBaseRefUsingFlags.item]
	call getBaseRefAtIndex
	add rsp, 8*8
	mov [getBaseRefUsingFlags.nextRef], rax



	.end:
	mov rax, [getBaseRefUsingFlags.nextRef]


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

; Assumes Refs are Processed
processing.getRefLettersAlloc:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getRefLettersAlloc.heapAddress qword at rbp-8  
	label getRefLettersAlloc.handleAllocatedMemory qword at rbp-16
	label getRefLettersAlloc.parsing qword at rbp-24 
	label getRefLettersAlloc.unprocessedCount qword at rbp-32
	label getRefLettersAlloc.newRef qword at rbp-40
	label getRefLettersAlloc.letters qword at rbp-48
	label getRefLettersAlloc.nextNewlineIndex qword at rbp-56
	label getRefLettersAlloc.list qword at rbp-64
	label getRefLettersAlloc.prevItem qword at rbp-72
	label getRefLettersAlloc.refRegistry qword at rbp-80
	label getRefLettersAlloc.item qword at rbp-88
	label getRefLettersAlloc.unprocessedParamCount qword at rbp-96
	label getRefLettersAlloc.nextRef qword at rbp-104
	label getRefLettersAlloc.refIndex qword at rbp-112
	label getRefLettersAlloc.index qword at rbp-120
	label getRefLettersAlloc.flags qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getRefLettersAlloc.item], rcx

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
	mov [getRefLettersAlloc.nextRef], rcx				; Begin as 0
	mov [getRefLettersAlloc.letters], rcx

	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.list
	mov rdx, [rbx]
	mov [getRefLettersAlloc.list], rdx				; Cache


	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.flags
	mov rdx, [rbx]
	cmp rdx, 1b							; REF_VALUE
	jne getRefLettersAlloc.refList

	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.valueAlloc
	mov rdx, [rbx]
	mov rax, rdx
	

	jmp getRefLettersAlloc.end
	.refList:


	sub rsp, 8*8
	mov rcx, [getRefLettersAlloc.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:				; Just ensure end is not reached
	mov rbx, [getRefLettersAlloc.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl getRefLettersAlloc.endItemList


	
	sub rsp, 8*8
	mov rcx, [getRefLettersAlloc.list]
	call [getNextItem]
	add rsp, 8*8
	mov [getRefLettersAlloc.nextRef], rax


	sub rsp, 8*8
	mov rcx, [getRefLettersAlloc.nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.valueAlloc
	mov rdx, [rbx]
	cmp rdx, 0
	jne getRefLettersAlloc.notFirstAlloc

	sub rsp, 8*8
	mov rbx, [getRefLettersAlloc.nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax
	

	jmp getRefLettersAlloc.nextRefItem

	.notFirstAlloc:

	sub rsp, 8*8
	mov rbx, [getRefLettersAlloc.nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rdx,rax
	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [appendLetters]				; Append
	add rsp, 8*8

	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.valueAlloc				; Allocation goes in item Ref's value alloc
	mov [rbx], rax



	jmp getRefLettersAlloc.nextRefItem
	.endItemList:

	.end:
	mov rbx, [getRefLettersAlloc.item]
	add rbx, Ref.valueAlloc
	mov rax, [rbx]


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

; Assumes Ref Items in List are Processed
processing.getRefLettersList:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label getRefLettersList.heapAddress qword at rbp-8  
	label getRefLettersList.handleAllocatedMemory qword at rbp-16
	label getRefLettersList.parsing qword at rbp-24 
	label getRefLettersList.unprocessedCount qword at rbp-32
	label getRefLettersList.newRef qword at rbp-40
	label getRefLettersList.letters qword at rbp-48
	label getRefLettersList.nextNewlineIndex qword at rbp-56
	label getRefLettersList.list qword at rbp-64
	label getRefLettersList.prevItem qword at rbp-72
	label getRefLettersList.refRegistry qword at rbp-80
	label getRefLettersList.item qword at rbp-88
	label getRefLettersList.unprocessedParamCount qword at rbp-96
	label getRefLettersList.nextRef qword at rbp-104
	label getRefLettersList.refIndex qword at rbp-112
	label getRefLettersList.index qword at rbp-120
	label getRefLettersList.flags qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [getRefLettersList.item], rcx

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
	mov [getRefLettersList.nextRef], rcx				; Begin as 0
	mov [getRefLettersList.letters], rcx

	mov rbx, [getRefLettersList.item]
	add rbx, Ref.list
	mov rdx, [rbx]
	mov [getRefLettersList.list], rdx				; Cache


	mov rbx, [getRefLettersList.item]
	add rbx, Ref.flags
	mov rdx, [rbx]
	cmp rdx, 1b							; REF_VALUE
	jne getRefLettersList.refList

	
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov rbx, [getRefLettersList.item]
	add rbx, Ref.listAlloc
	mov [rbx], rax


	sub rsp, 8*8
	mov rbx, [getRefLettersList.item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, rax
	mov rbx, [getRefLettersList.item]
	add rbx, Ref.listAlloc
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	jmp getRefLettersList.end
	.refList:


	sub rsp, 8*8
	mov rcx, [getRefLettersList.list]
	call [resetIndex]
	add rsp, 8*8



	.nextRefItem:				; Just ensure end is not reached
	mov rbx, [getRefLettersList.list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl getRefLettersList.endItemList


	
	sub rsp, 8*8
	mov rcx, [getRefLettersList.list]
	call [getNextItem]
	add rsp, 8*8
	mov [getRefLettersList.nextRef], rax


	sub rsp, 8*8
	mov rcx, [getRefLettersList.nextRef]
	call getRefLettersList
	add rsp, 8*8

	mov rbx, [getRefLettersList.item]
	add rbx, Ref.valueAlloc
	mov rdx, [rbx]
	cmp rdx, 0
	jne getRefLettersList.notFirstAlloc


	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov rbx, [getRefLettersList.item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax


	sub rsp, 8*8
	mov rbx, [getRefLettersList.nextRef]
	add rbx, Ref.listAlloc
	mov rdx, [rbx]
	mov rbx, [getRefLettersList.item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [extendList]
	add rsp, 8*8
	

	jmp getRefLettersList.nextRefItem

	.notFirstAlloc:

	sub rsp, 8*8
	mov rbx, [getRefLettersList.nextRef]
	add rbx, Ref.listAlloc
	mov rdx, [rbx]
	mov rbx, [getRefLettersList.item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [extendList]
	add rsp, 8*8
	






	jmp getRefLettersList.nextRefItem
	.endItemList:

	.end:
	mov rbx, [getRefLettersList.item]
	add rbx, Ref.valueAlloc
	mov rax, [rbx]


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