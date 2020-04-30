


section '.data' data readable writeable align 16



	struc RunCycles
		label .
		.refRegistry	dq 0		; Ref Registry has list of Refs, list of Defined Refs
		.parsing dq 0			; Parsing reference; Used with parsing passes
		.repRecordList	dq 0		; List of storage records with .rep file extension
		.cycleIndex	dq 0		; What cycle is currently running, must be less than max cycle count
		.maxCycleCount	dq 0		; Maximum amount of cycle runs.
		.repAllocation dq 0		; Rep allocation
	end struc


	

	; Used with address offsets
	virtual at 0
		RunCycles RunCycles
	end virtual

	; ---- Structures
	;element Element



	repFileExtensionLetters db '.rep',0
	repFileExtensionLettersMatcher db '*.rep',0
	currentDirRepFileExtensionLettersMatcher db '..\..\..\..\src\resources\*.rep',0


	storeFileDefinedRefLetters db 'storeFile',0
	restoreFileDefinedRefLetters db 'restoreFile',0
	retrieveFileDefinedRefLetters db 'retrieveFile',0
	lettersDefinedRefLetters db 'letters',0
	lettersSpaceDefinedRefLetters db ' ',0				; Shorthand when defining letters, just ' ' space token
	replaceLettersListDefinedRefLetters db 'replaceLettersList',0
	retrieveFileFlowRefLetters db 'retrieveFileFlow',0
	storeFileListRefLetters db 'storeFileList',0
	replaceLettersFlowDefinedRefLetters db 'replaceLettersFlow',0
	separatorDefinedRefLetters db 'separator',0


section '.text' code readable writeable executable align 16


; getRepFiles (once)
; append repAllocation
; parse
; process



runCycles:
namespace runCycles
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
	add rcx, RunCycles.repAllocation
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [handleAllocatedMemory]
	add rbx, RunCycles.refRegistry
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, RunCycles.parsing
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, RunCycles.repRecordList
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, RunCycles.cycleIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, RunCycles.maxCycleCount
	mov rax, 50						; 50 cycles can occur maximum, far fewer should be required, change this later if needed.
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, RunCycles.repAllocation
	mov rax, 0
	mov [rbx], rax

	mov rdx, newlineUnixLetters		;newlineWinLetters	;
	mov [newlineLetters], rdx


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

begin:
namespace begin
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label parsingAddr qword at rbp-32
	label repRecordList qword at rbp-40
	label runCyclesAddr qword at rbp-48
	label nextRef qword at rbp-56
	label storageRecord qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [runCyclesAddr], rcx


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
	call refRegistry.new
	add rsp, 8*8
	mov [refRegistryAddr], rax



	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.refRegistry
	mov rdx, [refRegistryAddr]
	mov [rbx], rdx					; Cache RefRegistry


	loadRefRegistryDefinedRefs:


	sub rsp, 8*8
	mov rcx, [runCyclesAddr]	
	call loadRefRegistry
	add rsp, 8*8



	sub rsp, 8*8
	call parsing.new
	add rsp, 8*8
	mov [parsingAddr], rax




	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.parsing
	mov rdx, [parsingAddr]
	mov [rbx], rdx					; Cache Parsing



	sub rsp, 8*8
	mov rcx, [runCyclesAddr]	
	call loadReps
	add rsp, 8*8




	sub rsp, 8*8
	mov rcx, [runCyclesAddr]	
	call loadRepAllocation
	add rsp, 8*8





	nextCycle:
	mov rbx, [runCyclesAddr]
	mov rdx, rbx
	add rbx, RunCycles.cycleIndex
	mov rcx, [rbx]
	add rdx, RunCycles.maxCycleCount
	mov r8, [rdx]
	cmp rcx, r8
	jnl endCycles
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.parsing
	mov rdx, [rbx]
	mov r8, rdx
	add rdx, Parsing.index
	add r8, Parsing.endIndex
	mov rcx, [rdx]
	mov r9, [r8]
	cmp r9, 0
	je firstCycle
	cmp rcx, r9
	jnl parsingComplete



	
	firstCycle:	

	sub rsp, 8*8
	mov rbx, [parsingAddr]
	add rbx, Parsing.index
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.refRegistry
	mov r8, [rbx]
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.repAllocation
	mov rdx, [rbx]
	mov rcx, [parsingAddr]
	call parsing.parseRep
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, 22222
	;call [debugNumMsg]
	add rsp, 8*8
	
	sub rsp, 8*8
	mov rbx, [parsingAddr]
	add rbx, Parsing.index
	mov rcx, [rbx]
	;call [debugNumMsg]
	add rsp, 8*8
		
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.cycleIndex
	mov rcx, 0
	mov [rbx], rcx					; Parsing resets cycleIndex when still within Parsing range

	jmp nextCycle				; This must change when working with separators
	parsingComplete:


	sub rsp, 8*8
	mov rcx, 38888
	;call [debugNumMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.refRegistry
	mov rcx, [rbx]
	;call refRegistry.unprocessedRefsCount
	add rsp, 8*8
	cmp rax, 0
	;je processingComplete





	sub rsp, 8*8
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.refRegistry
	mov r8, [rbx]
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.repAllocation
	mov rdx, [rbx]
	mov rcx, [parsingAddr]
	call processing.processRep
	add rsp, 8*8






	processingComplete:

	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.cycleIndex
	mov rcx, [rbx]
	add rcx, 1b
	mov [rbx], rcx


	jmp nextCycle
	
	endCycles:

	endList:




	mov rax, 0;[nextRef]



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

loadReps:
namespace loadReps
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label parsingAddr qword at rbp-32
	label repRecordList qword at rbp-40
	label runCyclesAddr qword at rbp-48
	label nextRef qword at rbp-56
	label storageRecord qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [runCyclesAddr], rcx


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
	call [newStorage]
	add rsp, 8*8
	mov [storageRecord], rax




	mov rbx, [storageRecord]
	add rbx, Record.location
	mov r8, currentDirLetter;currentDirRepFileExtensionLettersMatcher
	mov [rbx], r8


	



	sub rsp, 8*8
	mov rdx, repFileExtensionLetters
	mov rcx, [storageRecord]
	call [retrieveRecordNamesExtension]
	add rsp, 8*8
	mov [repRecordList], rax


	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.repRecordList
	mov rdx, [repRecordList]
	mov [rbx], rdx	





	endList:




	mov rax, 0;[nextRef]



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

loadRepAllocation:
namespace loadRepAllocation
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label parsingAddr qword at rbp-32
	label repRecordList qword at rbp-40
	label runCyclesAddr qword at rbp-48
	label storageRecordName qword at rbp-56
	label storageRecord qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [runCyclesAddr], rcx


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


	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.repRecordList
	mov rdx, [rbx]
	mov [repRecordList], rdx


	sub rsp, 8*8
	mov rcx, [repRecordList]
	call [resetIndex]
	add rsp, 8*8
	
	nextRepRecord:
	mov rbx, [repRecordList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endList


	sub rsp, 8*8
	mov rcx, [repRecordList]
	call [getNextItem]
	add rsp, 8*8
	mov [storageRecordName], rax

	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [storageRecord], rax
	
	

	mov rbx, [storageRecord]
	add rbx, Record.builtLocation
	mov r8, [storageRecordName];repFileExtensionLettersMatcher		; TO-DO: Handle other base dirs
	mov [rbx], r8

	

	sub rsp, 8*8
	mov rcx, [storageRecord]
	call [retrieve]
	add rsp, 8*8
	

	sub rsp, 8*8
	mov rbx, [storageRecord]
	add rbx, Record.allocAddr
	mov rcx, [rbx]
	call [copyLetters]				; allocate first, do not append
	add rsp, 8*8
	
	mov rbx, [repRecordList]
	add rbx, List.index
	mov rcx, [rbx]
	cmp rcx, 1b
	je endCopy			; CopyLetters only on first index, index incremented implicitly following getNextItem


	sub rsp, 8*8
	mov rdx, rax	
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.repAllocation	
	mov rcx, [rbx]
	call [appendLetters]
	add rsp, 8*8

	endCopy:
	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.repAllocation	
	mov [rbx], rax


	jmp nextRepRecord
	endList:




	mov rax, 0;[nextRef]



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

loadRefRegistry:
namespace loadRefRegistry
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label parsingAddr qword at rbp-32
	label repRecordList qword at rbp-40
	label runCyclesAddr qword at rbp-48
	label nextRef qword at rbp-56
	label storageRecord qword at rbp-64
	label lettersIndex qword at rbp-72
	label refRegistryAddr qword at rbp-80
	label newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [runCyclesAddr], rcx

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


	mov rbx, [runCyclesAddr]
	add rbx, RunCycles.refRegistry
	mov rdx, [rbx]
	mov [refRegistryAddr], rdx
	


	sub rsp, 8*8
	mov rcx, [refRegistryAddr]
	call processing.loadProcItemDefinedRefs
	add rsp, 8*8




	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRef], rax

	mov rbx, [newRef]
	add rbx, Ref.ref
	mov r9, lettersDefinedRefLetters		; Ref ref
	mov [rbx], r9

	mov rbx, [newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 1b
	mov [rbx], r9

	mov rbx, [newRef]
	add rbx, Ref.definedRefFlags			; definedRefFlags
	mov r9, 100b							; DEFINED_REF_LETTERS
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, [newRef]
	mov rcx, [refRegistryAddr]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRef], rax

	mov rbx, [newRef]
	add rbx, Ref.ref
	mov r9, lettersSpaceDefinedRefLetters		; Ref ref
	mov [rbx], r9

	mov rbx, [newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 1b
	mov [rbx], r9

	mov rbx, [newRef]
	add rbx, Ref.definedRefFlags			; definedRefFlags
	mov r9, 100b
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, [newRef]
	mov rcx, [refRegistryAddr]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8


	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRef], rax

	mov rbx, [newRef]
	add rbx, Ref.ref
	mov r9, separatorDefinedRefLetters		; Ref ref
	mov [rbx], r9

	mov rbx, [newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 1b
	mov [rbx], r9

	mov rbx, [newRef]
	add rbx, Ref.definedRefFlags			; definedRefFlags
	mov r9, 10000b
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, [newRef]
	mov rcx, [refRegistryAddr]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8





	mov rax, 0;[nextRef]



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