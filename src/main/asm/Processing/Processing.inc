


section '.data' data readable writeable align 16







	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM


	processRepMsg db 'Processing Rep...',0
	nextProcessRepRefMsg db 'Next Process Rep Ref:',0
	processRefValuesMsg db 'Processing Ref Values...',0
	unprocessedParamCountMsg db 'Unprocessed Param count:',0
	refBaseFlagsMsg db 'Refbase flags:',0
	definedRefFlagsMsg db 'Defined ref flags:',0
	baseRefMsg db 'Base Ref:',0
	baseRefDefinedRefFlagsMsg db 'BaseRef Defined RefFlags:',0
	definedRefFlagsMatchMsg	db 'Defined Ref flags match.',0
	processingLettersMsg db 'Processing Letters...',0
	processingListMsg db 'Processing List...',0
	gettingRefLettersListMsg db 'Getting Ref Letters List...',0

section '.text' code readable writeable executable align 16

;handle reservedword (parsing must categorize these flags)

processing:
namespace processing
processRep:
namespace processRep
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsedLetters qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newLineLetterLength qword at rbp-88
	label matchingStartIndex qword at rbp-96
	label nextRef qword at rbp-104
	label parsingRefs qword at rbp-112
	label parsingRefsIndex qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [letters], rdx	
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
	mov [parsingRefsIndex], rcx		; Begin as 0

	sub rsp, 8*8
	mov rcx, processRepMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [parsingAddr]
	add rbx, Parsing.parsingRefs
	mov r10, [rbx]
	mov [parsingRefs], r10

	sub rsp, 8*8
	mov rcx, [parsingRefs]
	call [resetIndex]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsingRefs]
	add rbx, List.itemsCount
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [parsingRefs]
	add rbx, List.index
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8



	nextRepItem:
	mov rbx, [parsingRefs]
	mov rdx, rbx
	add rbx, List.index
	mov rcx, [parsingRefsIndex]
	mov [rbx], rcx					; Nested functions change this
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endList


	sub rsp, 8*8
	mov rcx, [parsingRefs]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	mov rbx, [parsingRefs]
	add rbx, List.index
	mov rcx, [rbx]					; Nested functions change this. Cache here.
	mov [parsingRefsIndex], rcx


	sub rsp, 8*8
	mov rcx, nextProcessRepRefMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8
	
	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsingAddr]
	call processRefValues
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [refRegistryAddr]
	mov rdx, [nextRef]
	mov rcx, [parsingAddr]
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

	jmp nextRepItem
	endList:	


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

processRefValues:
namespace processRefValues
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label unprocessedParamCount qword at rbp-56
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


	mov [parsingAddr], rcx
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
	mov rcx, processRefValuesMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rcx, 0
	mov [prevItem], rcx			; Begin as 0
	mov [item], rcx			; Begin as 0
	mov [prevItemNesting], rcx
	mov [nesting], rcx
	mov [unprocessedParamCount], rcx

	mov rbx, [parsingAddr]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [resetIndex]
	add rsp, 8*8




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
	mov [item], rax


	mov rbx, [item]
	add rbx, Ref.flags
	mov r8, [rbx]
	mov rdx, 11b						; REF_LIST REF_VALUE
	and r8, rdx
	jz nextRefItem			; Skip when not REF_LIST or REF_VALUE

	sub rsp, 8*8
	mov rcx, [item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [unprocessedParamCount], rax
	cmp rax, 0
	jne hasUnprocessedParams		; Process when any params are unprocessed (param count may have increased: reprocessed)

	mov rbx, [item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne nextRefItem			; Skip when already processed (not unprocessed)

	hasUnprocessedParams:					; More params (appending) may be needed with further processing

	sub rsp, 8*8
	mov rcx, unprocessedParamCountMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [unprocessedParamCount]
	;call [debugNumMsg]
	add rsp, 8*8

	;definedRefFlags
	;DEFINED_REF_SEPARATOR	DEFINED_REF_REPLACE_LETTERS_LIST	DEFINED_REF_LETTERS	DEFINED_REF_RETRIEVE_FILE	DEFINED_REF_STORE_FILE


	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM




	; letters
	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsingAddr]
	mov qword [rsp+4*8], r10
	mov r9, 100b						; definedRefFlags	DEFINED_REF_LETTERS
	mov r8,	1b						; refBaseFlags		REF_BASE_DEFINED_REF_FIRST_PARAM
	mov rdx, 10b						; minParamCount
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8



	; appending
	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsing]
	mov qword [rsp+4*8], r10
	mov r9, 0						; definedRefFlags	No defined ref
	mov r8,	100b						; refBaseFlags		REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM
	mov rdx, 1b 						; minParamCount	
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8

	; List
	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsingAddr]
	mov qword [rsp+4*8], r10
	mov r9, 0						; definedRefFlags	No defined ref
	mov r8,	100b						; refBaseFlags		REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM
	mov rdx, 1b						; minParamCount
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8



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

processDefinedRefs:
namespace processDefinedRefs
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label matchIndex qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label parsingRefsList qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label prevItemNesting qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label unprocessedParamCount qword at rbp-120

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
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

	mov rbx, [parsingAddr]
	add rbx, Parsing.parsingRefs
	mov rcx, [rbx]
	mov [parsingRefsList], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [parsingRefsList]
	call [resetIndex]
	add rsp, 8*8



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
	mov [item], rax			; Item is REF_DEFINED or sometimes not (replaceLettersList's first ref that holds alloc)




	sub rsp, 8*8
	mov rcx, [item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [unprocessedParamCount], rax
	cmp rax, 0
	jne hasUnprocessedParams		; Process when any params are unprocessed. Should not matter with defined refs, but maybe will with future changes.

	mov rbx, [item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne nextRefItem			; Skip when already processed (not unprocessed)

	hasUnprocessedParams:					; More params (appending) may be needed with further processing


	;definedRefFlags
	;DEFINED_REF_SEPARATOR	DEFINED_REF_REPLACE_LETTERS_LIST	DEFINED_REF_LETTERS	DEFINED_REF_RETRIEVE_FILE	DEFINED_REF_STORE_FILE


	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM



	; processStoreFile
	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsingAddr]
	mov qword [rsp+4*8], r10
	mov r9, 1b						; definedRefFlags	DEFINED_REF_STORE_FILE
	mov r8,	10b						; refBaseFlags		REF_BASE_ITEM_DEFINED_REF
	mov rdx, 10b						; minParamCount
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8

	; processRestoreFile
	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsingAddr]
	mov qword [rsp+4*8], r10
	mov r9, 100000b						; definedRefFlags	DEFINED_REF_RESTORE_FILE
	mov r8,	10b						; refBaseFlags		REF_BASE_ITEM_DEFINED_REF
	mov rdx, 10b						; minParamCount
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8

	; processRetrieveFile
	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsingAddr]
	mov qword [rsp+4*8], r10
	mov r9, 10b						; definedRefFlags	DEFINED_REF_RETRIEVE_FILE
	mov r8,	10b						; refBaseFlags		REF_BASE_ITEM_DEFINED_REF
	mov rdx, 1b 						; minParamCount	
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8



	; processReplaceLettersList
	sub rsp, 8*8
	mov r11, [refRegistryAddr]
	mov qword [rsp+5*8], r11
	mov r10, [parsingAddr]
	mov qword [rsp+4*8], r10
	mov r9, 1000b						; definedRefFlags	DEFINED_REF_REPLACE_LETTERS_LIST
	mov r8,	1b						; refBaseFlags		REF_BASE_DEFINED_REF_FIRST_PARAM
	mov rdx, 100b 						; minParamCount	
	mov rcx, [nextRef]
	call processRefItem
	add rsp, 8*8




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

getUnprocessedParams:
namespace getUnprocessedParams
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label list qword at rbp-40
	label letters qword at rbp-48
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


	mov [item], rcx


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
	mov [unprocessedCount], rcx			; Begin as 0



	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [item], rax


	mov rbx, [item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne nextRefItem			; Skip when already processed (not unprocessed)

	mov rcx, [unprocessedCount]
	add rcx, 1b
	mov [unprocessedCount], rcx	; Increment when unprocessed


	jmp nextRefItem
	endItemList:


	completed:
	mov rax, [unprocessedCount]


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

getUnprocessedRegisteredParams:
namespace getUnprocessedRegisteredParams
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label list qword at rbp-40
	label letters qword at rbp-48
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


	mov [item], rcx
	mov [refRegistryAddr], rdx


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
	mov [unprocessedCount], rcx			; Begin as 0



	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.repIndex
	mov r8, [rbx]
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rdx, [rbx]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0
	je nextRefItem
	cmp rax, 2
	jle nextRefItem
	mov [nextRef], rax

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.unprocessed
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8


	mov rbx, [nextRef]
	add rbx, Ref.unprocessed
	mov rcx, [rbx]
	mov rdx, 1b
	cmp rcx, rdx
	jne nextRefItem			; Skip when already processed (not unprocessed)


	mov rcx, [unprocessedCount]
	add rcx, 1b
	mov [unprocessedCount], rcx	; Increment when unprocessed


	jmp nextRefItem
	endItemList:


	completed:
	mov rax, [unprocessedCount]


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

processLetters:
namespace processLetters
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	


	mov rcx, [definedRefFlags]
	mov r9, 100b						; definedRefFlags	DEFINED_REF_LETTERS
	cmp rcx, r9 
	jne completed					; Only attempt processing letters

	sub rsp, 8*8
	mov rcx, processingLettersMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8


	mov rbx, [list]
	add rbx, List.index
	mov rcx, 1b
	mov [rbx], rcx				; Param after lettersRef


	nextRefItem:				; Just ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [copyLetters]				
	add rsp, 8*8

	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax

	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done
	add rsp, 8*8
	jmp endItemList


	jmp nextRefItem
	endItemList:


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

processAppending:
namespace processAppending
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label processedCount qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	

	

	mov rcx, [definedRefFlags]
	mov r9, 0b						; definedRefFlags	None
	cmp rcx, r9 
	jne completed				; Only attempt processing letters

	mov r8, [item]
	add r8, Ref.flags
	mov rdx, [r8]
	mov r9, 1b						; REF_VALUE
	cmp rdx, r9 
	jne completed				; Only attempt processing letters


	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 0
	jne completed				; Appending depends on param registeredRefs being processed, not just the param

	

	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:						; Ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	mov rbx, [list]
	add rbx, List.index
	mov rdx, [rbx]
	cmp rdx, 1b
	jne notFirstIndex

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax


	
	jmp nextRefItem
	
	notFirstIndex:

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rdx,rax
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [appendLetters]				; Append
	add rsp, 8*8

	mov rbx, [item]
	add rbx, Ref.valueAlloc				; Allocation goes in item Ref's value alloc
	mov [rbx], rax





	jmp nextRefItem
	endItemList:


	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	notReady:


	completed:
	;mov rax, [nextRef]


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


processList:
namespace processList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label processedCount qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	

	

	mov rcx, [definedRefFlags]
	mov r9, 0b						; definedRefFlags	None
	cmp rcx, r9 
	jne completed				; Only attempt processing List



	mov r8, [item]
	add r8, Ref.flags
	mov rdx, [r8]
	mov r9, 10b						; REF_LIST
	cmp rdx, r9 
	jne completed				; Only attempt processing letters


	sub rsp, 8*8
	mov rcx, processingListMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [item]
	add r8, Ref.ref
	mov rcx, [r8]
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 0
	jne completed				; Appending depends on param registeredRefs being processed, not just the param

	sub rsp, 8*8
	mov rcx, [item]
	call getRefLettersList
	add rsp, 8*8




	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	notReady:


	completed:
	;mov rax, [nextRef]


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


processStoreFile:
namespace processStoreFile
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label processedCount qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	label record qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	


	mov rcx, [definedRefFlags]
	mov r9, 1b						; definedRefFlags	DEFINED_REF_STORE_FILE
	cmp rcx, r9 
	jne completed				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 0
	jne completed				; This definedRef depends on param registeredRefs being processed, not just the param



	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8




	nextRefItem:						; Ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax



	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [record], rax

	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [record]
	add rbx, Record.builtLocation
	mov [rbx], rax


	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	mov rbx, [nextRef]
	add rbx, Ref.flags
	mov rdx, [rbx]
	mov rcx, 10b					; REF_LIST
	cmp rcx, rdx
	je listLetters

	
	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	jmp storeRefFile
	listLetters:

	mov r8, [nextRef]
	add r8, Ref.valueAlloc
	mov rcx, [r8]
	sub rsp, 8*8
	call [listAsLetters]
	add rsp, 8*8



	storeRefFile:

	sub rsp, 8*8
	mov rdx, rax 
	mov rcx, [record]
	call [storeLetters]
	add rsp, 8*8



	;jmp nextRefItem
	endItemList:



	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8

	notReady:


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


processRestoreFile:
namespace processRestoreFile
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label processedCount qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	label record qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	


	mov rcx, [definedRefFlags]
	mov r9, 100000b						; definedRefFlags	DEFINED_REF_RESTORE_FILE
	cmp rcx, r9 
	jne completed				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 0
	jne completed				; This definedRef depends on param registeredRefs being processed, not just the param



	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8




	nextRefItem:						; Ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax



	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [record], rax

	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [record]
	add rbx, Record.builtLocation
	mov [rbx], rax


	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	mov rbx, [nextRef]
	add rbx, Ref.flags
	mov rdx, [rbx]
	mov rcx, 10b					; REF_LIST
	cmp rcx, rdx
	je listLetters

	
	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	jmp storeRefFile
	listLetters:

	mov r8, [nextRef]
	add r8, Ref.valueAlloc
	mov rcx, [r8]
	sub rsp, 8*8
	call [listAsLetters]
	add rsp, 8*8



	storeRefFile:

	sub rsp, 8*8
	mov rdx, rax 
	mov rcx, [record]
	call [restoreLetters]
	add rsp, 8*8



	;jmp nextRefItem
	endItemList:



	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8

	notReady:


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

processRetrieveFile:
namespace processRetrieveFile
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label processedCount qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	label record qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	


	mov rcx, [definedRefFlags]
	mov r9, 10b						; definedRefFlags	DEFINED_REF_RETRIEVE_FILE
	cmp rcx, r9 
	jne completed				; Only attempt processing this definedRef

	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 1b						; Second param can be unprocessed. TO-DO: improve.
	jnle completed				; This definedRef depends on param registeredRefs being processed, not just the param



	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:						; Ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [record], rax

	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [record]
	add rbx, Record.builtLocation
	mov [rbx], rax


	sub rsp, 8*8
	mov rcx, [record]
	call [retrieve]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax



	mov rbx, [record]
	add rbx, Record.allocAddr
	mov rdx, [nextRef]
	add rdx, Ref.valueAlloc
	mov r8, [rbx]
	mov [rdx], r8





	;jmp nextRefItem
	endItemList:


	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	notReady:


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

processReplaceLettersList:
namespace processReplaceLettersList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*19);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label processedCount qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label definedRefFlags qword at rbp-120
	label record qword at rbp-128
	label param1 qword at rbp-136
	label param2 qword at rbp-144
	label param3 qword at rbp-152

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [parsingAddr], rcx
	mov [item], rdx	
	mov [refRegistryAddr], r8
	mov [definedRefFlags], r9

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

	


	mov rcx, [definedRefFlags]
	mov r9, 1000b						; definedRefFlags	DEFINED_REF_REPLACE_LETTERS_LIST
	cmp rcx, r9 
	jne completed				; Only attempt processing this definedRef



	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	sub rsp, 8*8
	mov rcx, rax
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call getUnprocessedRegisteredParams
	add rsp, 8*8
	cmp rax, 10b
	jnle completed				; Separator, replaceLettersList definedref can be unprocessed? This definedRef depends on param registeredRefs being processed, not just the param




	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:						; Ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax	; replaceLettersLisst


	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax	; letters

	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8
	mov [param1], rax	; letters


	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax	; list
	mov rbx, [nextRef]
	add rbx, Ref.valueAlloc
	mov rax, [rbx]
	mov [param2], rax	; letters


	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax	; containsLetters

	mov rbx, [nextRef]
	add rbx, Ref.ref
	sub rsp, 8*8
	mov rcx, [rbx]
	call [copyLetters]
	add rsp, 8*8
	mov [param3], rax	; containsLetters


	sub rsp, 8*8
	mov r8, [param3]
	mov rdx, [param2]
	mov rcx, [param1]
	call [replaceContainsLettersWithList]
	add rsp, 8*8

	mov rdx, [item]
	add rdx, Ref.valueAlloc
	mov [rdx], rax





	;jmp nextRefItem
	endItemList:


	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed				; Done, refs processed
	add rsp, 8*8


	notReady:


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


defineAsProcessed:
namespace defineAsProcessed
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*14);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [item], rcx
	mov [refRegistryAddr], rdx	

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

	


	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache



	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8




	nextRefItem:
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList



	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	

	mov rbx, [nextRef]
	add rbx, Ref.unprocessed
	mov rcx, 0					; Param as processed
	mov [rbx], rcx


	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.repIndex
	mov r8, [rbx]
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rdx, [rbx]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0
	je nextRefItem
	cmp rax, 2
	jle nextRefItem
	add rax, Ref.unprocessed
	mov rcx, 0
	mov [rax], rcx					; Processed in Registry also
	



	jmp nextRefItem
	endItemList:

	mov rbx, [item]
	add rbx, Ref.unprocessed
	mov rcx, 0				; Ref as processed
	mov [rbx], rcx

	sub rsp, 8*8
	mov rbx, [item]
	add rbx, Ref.repIndex
	mov r8, [rbx]
	mov rbx, [item]
	add rbx, Ref.ref
	mov rdx, [rbx]
	mov rcx, [refRegistryAddr]
	call refRegistry.getRegisteredRef
	add rsp, 8*8
	cmp rax, 0
	je completed
	cmp rax, 2
	jle completed
	add rax, Ref.unprocessed
	mov rcx, 0
	mov [rax], rcx					; Processed in Registry also
	


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

; processRefItem
	; is ref the defined ref or not that must be processed, skip otherwise
	; is the param count sufficient, skip otherwise
	; are the params unprocessed, skip otherwise
		; processLetters
		; processAppending
	; define items and params as unprocessed

processRefItem:
namespace processRefItem
	push rbp 
	mov rbp, rsp 


	mov r10, [rsp+8*6]
	mov r11, [rsp+8*7]

	sub rsp, (8*17);+(8*6)
	


	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label definedRefFlags qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label baseRef qword at rbp-40
	label definedItemIndex qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label list qword at rbp-64
	label parsingAddr qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label minParamCount qword at rbp-120
	label refBaseFlags qword at rbp-128
	label processedCount qword at rbp-136

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [item], rcx
	mov [minParamCount], rdx	
	mov [refBaseFlags], r8			; 
	mov [definedRefFlags], r9		; Defined Ref flags
	mov [parsingAddr], r10
	mov [refRegistryAddr], r11

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
	mov rcx, refBaseFlagsMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [refBaseFlags]
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, definedRefFlagsMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [definedRefFlags]
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [unprocessedParamCount], rax
	cmp rax, 0
	jne hasUnprocessedParams			; Can process

	mov rbx, [item]
	add rbx, Ref.unprocessed
	mov r8, [rbx]
	mov rdx, 1b
	cmp r8, rdx
	jne completed					; Item itself also processed. No need to process


	hasUnprocessedParams:




	
	sub rsp, 8*8
	mov rdx, [refBaseFlags]
	mov rcx, [item]
	call getBaseRefUsingFlags
	add rsp, 8*8
	mov [baseRef], rax

	sub rsp, 8*8
	mov rcx, baseRefMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [baseRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, baseRefDefinedRefFlagsMsg
	;call [debugLetters]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [baseRef]
	add r8, Ref.definedRefFlags
	mov rcx, [r8]
	;call [debugNumMsg]
	add rsp, 8*8

	mov r8, [baseRef]
	add r8, Ref.definedRefFlags
	mov r10, [r8]
	mov r9, [definedRefFlags]
	cmp r10, r9
	jne completed					; Not same, skip

	sub rsp, 8*8
	mov rcx, definedRefFlagsMatchMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rbx, [item]
	add rbx, Ref.list
	mov rdx, [rbx]
	add rdx, List.itemsCount
	mov r8, [rdx]
	mov rcx, [minParamCount]
	cmp r8, rcx
	jnge completed					; Insufficient params, skip



	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processLetters					
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processAppending				
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processList				
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processStoreFile	
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processRestoreFile	
	add rsp, 8*8


	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processRetrieveFile			
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processReplaceLettersList			
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [item]
	call getUnprocessedParams
	add rsp, 8*8
	mov [unprocessedParamCount], rax
	
	mov r9,[unprocessedParamCount]
	mov rcx, 0
	cmp r9, rcx
	jg notReady				; Still has unprocessed params

	sub rsp, 8*8
	mov rdx, [refRegistryAddr]
	mov rcx, [item]
	call defineAsProcessed					; Done, refs processed
	add rsp, 8*8


	notReady:




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


; item index is 0
; item's list first Ref index is 1
; Next item is last plus 1
getBaseRefAtIndex:
namespace getBaseRefAtIndex
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label nesting qword at rbp-112
	label index qword at rbp-120
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [item], rcx
	mov [index], rdx	

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
	mov [nextRef], rcx				; Begin as 0


	mov rdx, [index]
	cmp rdx, 0
	jne useParamList

	mov rbx, [item]
	mov [nextRef], rbx
	
	jmp completed





	useParamList:


	mov rbx, [item]
	add rbx, Ref.list
	mov rcx, [rbx]
	mov [list], rcx		; Cache

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8

	mov rbx, [list]
	add rbx, List.index
	mov r8, [index]
	sub r8, 1b					; Item was included in index, so List would not include it
	mov [rbx], r8


	nextRefItem:
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	endItemList:	

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

getBaseRefUsingFlags:
namespace getBaseRefUsingFlags
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label refIndex qword at rbp-112
	label index qword at rbp-120
	label flags qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [item], rcx
	mov [flags], rdx	

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
	mov [nextRef], rcx				; Begin as 0
	mov [refIndex], rcx

	; Ref Base flags
	; REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	REF_BASE_ITEM_DEFINED_REF	REF_BASE_DEFINED_REF_FIRST_PARAM

	mov rcx, [flags]
	cmp rcx, 1b
	jne notFirst


	mov rdx, 1b
	mov [refIndex], rdx


	jmp getIndex
	notFirst:

	mov rcx, [flags]
	cmp rcx, 10b
	jne notItem

	mov rdx, 0b
	mov [refIndex], rdx

	jmp getIndex
	notItem:


	mov rcx, [flags]
	cmp rcx, 100b
	jne completed					; Should not get here

	mov rdx, 0b
	mov [refIndex], rdx



	getIndex:

	sub rsp, 8*8
	mov rdx, [refIndex]
	mov rcx, [item]
	call getBaseRefAtIndex
	add rsp, 8*8
	mov [nextRef], rax



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

; Assumes Refs are Processed
getRefLettersAlloc:
namespace getRefLettersAlloc
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label refIndex qword at rbp-112
	label index qword at rbp-120
	label flags qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [item], rcx

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
	mov [nextRef], rcx				; Begin as 0
	mov [letters], rcx

	mov rbx, [item]
	add rbx, Ref.list
	mov rdx, [rbx]
	mov [list], rdx				; Cache


	mov rbx, [item]
	add rbx, Ref.flags
	mov rdx, [rbx]
	cmp rdx, 1b							; REF_VALUE
	jne refList

	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rdx, [rbx]
	mov rax, rdx
	

	jmp completed
	refList:


	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:				; Just ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersAlloc
	add rsp, 8*8

	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rdx, [rbx]
	cmp rdx, 0
	jne notFirstAlloc

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax
	

	jmp nextRefItem

	notFirstAlloc:

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rdx,rax
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [appendLetters]				; Append
	add rsp, 8*8

	mov rbx, [item]
	add rbx, Ref.valueAlloc				; Allocation goes in item Ref's value alloc
	mov [rbx], rax



	jmp nextRefItem
	endItemList:

	completed:
	mov rbx, [item]
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

; Assumes Ref Items in List are Processed
getRefLettersList:
namespace getRefLettersList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*16);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsingAddr qword at rbp-24 
	label unprocessedCount qword at rbp-32
	label newRef qword at rbp-40
	label letters qword at rbp-48
	label nextNewlineIndex qword at rbp-56
	label list qword at rbp-64
	label prevItem qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label item qword at rbp-88
	label unprocessedParamCount qword at rbp-96
	label nextRef qword at rbp-104
	label refIndex qword at rbp-112
	label index qword at rbp-120
	label flags qword at rbp-128
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [item], rcx

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
	mov rcx, gettingRefLettersListMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov r8, [item]
	add r8, Ref.ref
	mov rcx, [r8]
	;call [debugLettersMsg]
	add rsp, 8*8

	mov rcx, 0
	mov [nextRef], rcx				; Begin as 0
	mov [letters], rcx

	mov rbx, [item]
	add rbx, Ref.list
	mov rdx, [rbx]
	mov [list], rdx				; Cache


	mov rbx, [item]
	add rbx, Ref.flags
	mov rdx, [rbx]
	cmp rdx, 1b							; REF_VALUE
	jne refList

	

	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov rbx, [item]
	add rbx, Ref.listAlloc
	mov [rbx], rax


	sub rsp, 8*8
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, rax
	mov rbx, [item]
	add rbx, Ref.listAlloc
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8


	jmp completed
	refList:


	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8



	nextRefItem:				; Just ensure end is not reached
	mov rbx, [list]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItemList


	
	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	mov rbx, [nextRef]
	add rbx, Ref.flags
	mov rdx, [rbx]
	mov rcx, 10b									; REF_LIST
	cmp rdx, rcx
	jne noNextRefListClearing

	mov rbx, [nextRef]
	add rbx, Ref.valueAlloc
	mov rcx, 0
	mov [rbx], rcx									; Rebuild nextRef valueAlloc when it is a List. Do not duplicate when it built this separately

	noNextRefListClearing:




	sub rsp, 8*8
	mov rcx, [nextRef]
	call getRefLettersList
	add rsp, 8*8

	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rdx, [rbx]
	cmp rdx, 0
	jne notFirstAlloc



	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov [rbx], rax


	mov rbx, [nextRef]
	add rbx, Ref.flags
	mov rdx, [rbx]
	mov rcx, 10b									; REF_LIST
	cmp rdx, rcx
	je nextRefIsList


	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.listAlloc
	mov rdx, [rbx]
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [extendList]
	add rsp, 8*8


	

	jmp nextRefItem

	notFirstAlloc:




	mov rbx, [nextRef]
	add rbx, Ref.flags
	mov rdx, [rbx]
	mov rcx, 10b								; REF_LIST
	cmp rdx, rcx
	je nextRefIsList

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.listAlloc
	mov rdx, [rbx]
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [extendList]
	add rsp, 8*8


	jmp nextRefItem
	nextRefIsList:


	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.valueAlloc
	mov rdx, [rbx]
	mov rbx, [item]
	add rbx, Ref.valueAlloc
	mov rcx, [rbx]
	call [extendList]
	add rsp, 8*8

	






	jmp nextRefItem
	endItemList:

	completed:



	mov rbx, [item]
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


end namespace