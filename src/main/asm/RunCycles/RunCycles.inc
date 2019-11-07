


section '.data' data readable writeable align 16



	struc RunCycles
		label .
		.refRegistry	dq 0		; Ref Registry has list of Refs, list of Defined Refs
		.parsing dq 0			; Parsing reference; Used with parsing passes
		.repRecordList	dq 0		; List of storage records with .rep file extension
		.repAllocation dq 0		; Rep allocation
	end struc


	

	; Used with address offsets
	virtual at 0
		RunCycles RunCycles
	end virtual

	; ---- Structures
	;element Element



	repFileExtensionLettersMatcher db '*.rep',0


	storeFileDefinedRefLetters db 'storeFile',0
	retrieveFileDefinedRefLetters db 'retrieveFile',0
	lettersDefinedRefLetters db 'letters',0
	replaceLettersListDefinedRefLetters db 'replaceLettersList',0
	separatorDefinedRefLetters db 'separator',0


section '.text' code readable writeable executable align 16


; getRepFiles (once)
; append repAllocation
; parse
; process



runCycles:
namespace runCycles
runCycles.new:
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
	add rcx, RunCycles.repAllocation
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [new.heapAddress]
	call [ HeapAlloc] 
	mov [new.handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [new.handleAllocatedMemory]
	add rbx, RunCycles.refRegistry
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, RunCycles.parsing
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, RunCycles.repRecordList
	mov rax, 0
	mov [rbx], rax
	mov rbx, [new.handleAllocatedMemory]
	add rbx, RunCycles.repAllocation
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

runCycles.begin:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label begin.heapAddress qword at rbp-8  
	label begin.handleAllocatedMemory qword at rbp-16
	label begin.list qword at rbp-24 
	label begin.parsing qword at rbp-32
	label begin.repRecordList qword at rbp-40
	label begin.runCyclesAddr qword at rbp-48
	label begin.nextRef qword at rbp-56
	label begin.storageRecord qword at rbp-64
	label begin.lettersIndex qword at rbp-72
	label begin.refRegistry qword at rbp-80
	label begin.newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [begin.runCyclesAddr], rcx


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
	mov [begin.refRegistry], rax

	mov rbx, [begin.runCyclesAddr]
	add rbx, RunCycles.refRegistry
	mov rdx, [begin.refRegistry]
	mov [rbx], rdx					; Cache RefRegistry


	.loadRefRegistryDefinedRefs:


	sub rsp, 8*8
	mov rcx, [begin.runCyclesAddr]	
	call loadRefRegistry
	add rsp, 8*8




	sub rsp, 8*8
	call parsing.new
	add rsp, 8*8
	mov [begin.parsing], rax

	mov rbx, [begin.runCyclesAddr]
	add rbx, RunCycles.parsing
	mov rdx, [begin.parsing]
	mov [rbx], rdx					; Cache Parsing


	sub rsp, 8*8
	mov rcx, [begin.runCyclesAddr]	
	call loadReps
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [begin.runCyclesAddr]	
	call loadRepAllocation
	add rsp, 8*8



	


	.endList:




	mov rax, 0;[begin.nextRef]



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

runCycles.loadReps:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label loadReps.heapAddress qword at rbp-8  
	label loadReps.handleAllocatedMemory qword at rbp-16
	label loadReps.list qword at rbp-24 
	label loadReps.parsing qword at rbp-32
	label loadReps.repRecordList qword at rbp-40
	label loadReps.runCyclesAddr qword at rbp-48
	label loadReps.nextRef qword at rbp-56
	label loadReps.storageRecord qword at rbp-64
	label loadReps.lettersIndex qword at rbp-72
	label loadReps.refRegistry qword at rbp-80
	label loadReps.newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [loadReps.runCyclesAddr], rcx


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
	mov [loadReps.storageRecord], rax

	mov rbx, [loadReps.storageRecord]
	add rbx, Record.location
	mov r8, repFileExtensionLettersMatcher
	mov [rbx], r8
	

	sub rsp, 8*8
	mov rcx, [loadReps.storageRecord]
	call [retrieveRecordNames]
	add rsp, 8*8
	mov [loadReps.repRecordList], rax

	mov rbx, [loadReps.runCyclesAddr]
	add rbx, RunCycles.repRecordList
	mov rdx, [loadReps.repRecordList]
	mov [rbx], rdx	


	.endList:




	mov rax, 0;[loadReps.nextRef]



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

runCycles.loadRepAllocation:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label loadRepAllocation.heapAddress qword at rbp-8  
	label loadRepAllocation.handleAllocatedMemory qword at rbp-16
	label loadRepAllocation.list qword at rbp-24 
	label loadRepAllocation.parsing qword at rbp-32
	label loadRepAllocation.repRecordList qword at rbp-40
	label loadRepAllocation.runCyclesAddr qword at rbp-48
	label loadRepAllocation.storageRecordName qword at rbp-56
	label loadRepAllocation.storageRecord qword at rbp-64
	label loadRepAllocation.lettersIndex qword at rbp-72
	label loadRepAllocation.refRegistry qword at rbp-80
	label loadRepAllocation.newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [loadRepAllocation.runCyclesAddr], rcx


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


	mov rbx, [loadRepAllocation.runCyclesAddr]
	add rbx, RunCycles.repRecordList
	mov rdx, [rbx]
	mov [loadRepAllocation.repRecordList], rdx


	sub rsp, 8*8
	mov rcx, [loadRepAllocation.repRecordList]
	call [resetIndex]
	add rsp, 8*8
	
	.nextRepRecord:
	mov rbx, [loadRepAllocation.repRecordList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl loadRepAllocation.endList


	sub rsp, 8*8
	mov rcx, [loadRepAllocation.repRecordList]
	call [getNextItem]
	add rsp, 8*8
	mov [loadRepAllocation.storageRecordName], rax

	sub rsp, 8*8
	call [newStorage]
	add rsp, 8*8
	mov [loadRepAllocation.storageRecord], rax

	mov rbx, [loadRepAllocation.storageRecord]
	add rbx, Record.builtLocation
	mov r8, repFileExtensionLettersMatcher
	mov [rbx], r8
	

	sub rsp, 8*8
	mov rcx, [loadRepAllocation.storageRecord]
	call [retrieve]
	add rsp, 8*8
	mov [loadRepAllocation.repRecordList], rax

	


	;.repAllocation	;;;;;;;;;;;;;;;;;;;;;;;;;

	.endList:




	mov rax, 0;[loadRepAllocation.nextRef]



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

runCycles.loadRefRegistry:
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*11);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label loadRefRegistry.heapAddress qword at rbp-8  
	label loadRefRegistry.handleAllocatedMemory qword at rbp-16
	label loadRefRegistry.list qword at rbp-24 
	label loadRefRegistry.parsing qword at rbp-32
	label loadRefRegistry.repRecordList qword at rbp-40
	label loadRefRegistry.runCyclesAddr qword at rbp-48
	label loadRefRegistry.nextRef qword at rbp-56
	label loadRefRegistry.storageRecord qword at rbp-64
	label loadRefRegistry.lettersIndex qword at rbp-72
	label loadRefRegistry.refRegistry qword at rbp-80
	label loadRefRegistry.newRef qword at rbp-88
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [loadRefRegistry.runCyclesAddr], rcx

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


	mov rbx, [loadRefRegistry.runCyclesAddr]
	add rbx, RunCycles.refRegistry
	mov rdx, [rbx]
	mov [loadRefRegistry.refRegistry], rdx
	

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [loadRefRegistry.newRef], rax

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.ref
	mov r9, storeFileDefinedRefLetters		; Ref ref
	mov [rbx], r9

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 10b
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, [loadRefRegistry.newRef]
	mov rcx, [loadRefRegistry.refRegistry]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [loadRefRegistry.newRef], rax

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.ref
	mov r9, retrieveFileDefinedRefLetters		; Ref ref
	mov [rbx], r9

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 10b
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, retrieveFileDefinedRefLetters
	mov rcx, [loadRefRegistry.newRef]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [loadRefRegistry.newRef], rax

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.ref
	mov r9, lettersDefinedRefLetters		; Ref ref
	mov [rbx], r9

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 1b
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, [loadRefRegistry.newRef]
	mov rcx, [loadRefRegistry.refRegistry]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [loadRefRegistry.newRef], rax

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.ref
	mov r9, replaceLettersListDefinedRefLetters	; Ref ref
	mov [rbx], r9

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 11b
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, [loadRefRegistry.newRef]
	mov rcx, [loadRefRegistry.refRegistry]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8

	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [loadRefRegistry.newRef], rax

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.ref
	mov r9, separatorDefinedRefLetters		; Ref ref
	mov [rbx], r9

	mov rbx, [loadRefRegistry.newRef]
	add rbx, Ref.paramCount				; Param count
	mov r9, 1b
	mov [rbx], r9

	sub rsp, 8*8
	mov rdx, [loadRefRegistry.newRef]
	mov rcx, [loadRefRegistry.refRegistry]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8





	mov rax, 0;[loadRefRegistry.nextRef]



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