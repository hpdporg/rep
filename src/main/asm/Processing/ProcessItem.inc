


section '.data' data readable writeable align 16




	struc ProcessItem
		label .
		.label	dq 0		; Identifier: Letters or Numeric
		.refFlags dq 0		; Flags
		.definedRefFlags dq 0	; Defined Refs may use flags
		.paramCount dq 0	; Defined Refs may have params
		.refBaseFlags dq 0	; 
		.minParamCount dq 0	; Defined Refs may have params
	end struc

	; Used with address offsets
	virtual at 0
		ProcessItem ProcessItem
	end virtual

	namespace processing
	processItemTable:
	;Label,refFlags,definedRefFlags,paramCount,refBaseFlags,minParamCount
	dq storeFileDefinedRefLetters,100b,1,10b,10b,10b
	dq restoreFileDefinedRefLetters,100b,100000b,10b,10b,10b
	dq retrieveFileDefinedRefLetters,100b,10b,10b,10b,1b
	dq replaceLettersListDefinedRefLetters,100b,1000b,11b,1b,100b
	dq 0,1,100b,1b,1b,10b	; Letters
	dq 0,1,0,1b,100b,1b	; Appending
	dq 0,10,0,1b,100b,1b	; List
	endProcessItemTable:
	end namespace

	processItemList dq 0


section '.text' code readable writeable executable align 16




namespace processing
newProcessItem:
namespace newProcessItem
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


	sub rsp, 8*8
	mov rcx, ProcessItem.minParamCount
	call [allocateNew]
	mov [handleAllocatedMemory], rax
	add rsp, 8*8



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

getProcessItemList:
namespace getProcessItemList
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*12);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label processItemAlloc qword at rbp-64
	label entryCount qword at rbp-72
	label entryIndex qword at rbp-80
	label entryColIndex qword at rbp-88
	label entryOffset qword at rbp-96

	;virtual at rbp-64
	;	.list List
	;end virtual	


	;mov [numExpAddr], rcx
	

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


	mov rdx, [processItemList]
	cmp rdx, 0
	
	jne completed				; Already initialized, just return alloc


	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [processItemList], rax

	mov rcx, endProcessItemTable
	mov r8, processItemTable
	sub rcx, r8			; = With 7 entries this would be 336. / 6 (cols) /8 (dq) = 7 entries
	mov rdx, 0
	mov rax, rcx
	mov rcx, 6			; 6 columns
	idiv rcx
	mov rcx, 8			; Size of each entry, dq
	idiv rcx
	mov [entryCount], rax	

	mov rcx, 0
	mov [entryIndex], rcx		; Begin as 0
	mov [entryColIndex], rcx	; Begin as 0
	mov [entryOffset], rcx	; Begin as 0



	nextProcessItem:
	mov rcx, [entryIndex]
	mov rdx, [entryCount]
	cmp rcx, rdx
	jnl endItems



	sub rsp, 8*8
	call newProcessItem
	add rsp, 8*8
	mov [processItemAlloc], rax


	mov rcx, 0
	mov [entryColIndex], rcx	; Begin as 0


	nextColVal:
	mov r10, [entryColIndex]
	mov r11, 6
	cmp r10, r11
	jnl endColVals

	mov rbx, processItemTable
	mov r9, [entryOffset]
	add rbx, r9
	mov r13, [rbx]			; Table col val

	mov rbx, [processItemAlloc]
	mov rdx, 0
	mov rax, 8			; Col size 8 dq
	mov rcx, [entryColIndex]
	imul rcx
	add rbx, rax 
	mov [rbx], r13			; Assumes table spacing and alloc item order same



	mov r14, [entryColIndex]
	add r14, 1b			; Increment
	mov [entryColIndex], r14

	mov r15, [entryOffset]
	add r15, 8			; entry size 8 dq
	mov [entryOffset], r15

	jmp nextColVal
	endColVals:


	sub rsp, 8*8
	mov rdx, [processItemAlloc]
	mov rcx, [processItemList]
	call [newLastItem]
	add rsp, 8*8


	mov r14, [entryIndex]
	add r14, 1b			; Increment
	mov [entryIndex], r14


	jmp nextProcessItem
	endItems:






	completed:

	mov rax, [processItemList]



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

loadProcItemDefinedRefs:
namespace loadProcItemDefinedRefs
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*15);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label matchFlow qword at rbp-24 
	label matchIndexCount qword at rbp-32
	label numExpAddr qword at rbp-40
	label lettersAlloc qword at rbp-48
	label expExtList qword at rbp-56
	label processItemAddr qword at rbp-64
	label entryCount qword at rbp-72
	label entryIndex qword at rbp-80
	label entryColIndex qword at rbp-88
	label entryOffset qword at rbp-96
	label processItemListAddr qword at rbp-104
	label newRefAddr qword at rbp-112
	label refRegistryAddr qword at rbp-120

	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [refRegistryAddr], rcx
	

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
	call getProcessItemList
	add rsp, 8*8
	mov [processItemListAddr], rax


	mov rcx, 0
	mov [entryIndex], rcx		; Begin as 0

	sub rsp, 8*8
	mov rcx, [processItemListAddr]
	call [resetIndex]
	add rsp, 8*8


	nextProcessItem:
	mov rbx, [processItemListAddr]
	mov r8, rbx
	add rbx, List.index
	add r8, List.itemsCount
	mov rcx, [rbx]
	mov rdx, [r8]
	cmp rcx, rdx
	jnl endItems



	sub rsp, 8*8
	call ref.new
	add rsp, 8*8
	mov [newRefAddr], rax

	sub rsp, 8*8
	mov rcx, [processItemListAddr]
	call [getNextItem]
	add rsp, 8*8
	mov [processItemAddr], rax

	mov r10, [processItemAddr]
	add r10, ProcessItem.refFlags
	mov rdx, [r10]
	cmp rdx, 100b		; REF_DEFINED		100b			2	; 
	jne nextProcessItem



	mov rbx, [newRefAddr]
	add rbx, Ref.ref
	mov r10, [processItemAddr]
	add r10, ProcessItem.label
	mov r9, [r10]
	mov [rbx], r9



	mov rbx, [newRefAddr]
	add rbx, Ref.paramCount
	mov r10, [processItemAddr]
	add r10, ProcessItem.paramCount
	mov r9, [r10]
	mov [rbx], r9


	mov rbx, [newRefAddr]
	add rbx, Ref.definedRefFlags
	mov r10, [processItemAddr]
	add r10, ProcessItem.definedRefFlags
	mov r9, [r10]
	mov [rbx], r9


	sub rsp, 8*8
	mov rdx, [newRefAddr]
	mov rcx, [refRegistryAddr]
	call refRegistry.newLastRegisteredDefinedRef
	add rsp, 8*8



	jmp nextProcessItem
	endItems:



	sub rsp, 8*8
	mov rcx, [processItemListAddr]
	call [resetIndex]
	add rsp, 8*8




	completed:

	mov rax, 0



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