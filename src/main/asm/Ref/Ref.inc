


section '.data' data readable writeable align 16


	struc Ref
		label .
		.ref	dq 0		; Identifier: Letters or Numeric
		.flags dq 0		; Flags
		.unprocessed dq 0	; 0 or 1
		.paramCount dq 0	; Defined Refs may have params
		.repIndex dq 0		; Index into rep
		.valueAlloc dq 0	; Processed Value alloc
		.listAlloc dq 0		; List alloc. Used by Lists
		.definedRefFlags dq 0	; Defined Refs may use flags
		.list dq 0		; Values, Refs list, Params
		.flowAlloc dq 0		; Flow ref
	end struc


	

	; Used with address offsets
	virtual at 0
		Ref Ref
	end virtual

	; ---- Structures
	;element Element




	; REF Flags
	; REF_VALUE		1b			0	; 
	; REF_LIST		10b			1	; 
	; REF_DEFINED		100b			2	; 
	; REF_FILTER		1000b			3	; 
	; REF_FLOW		1000b			3	; 



	

	; DEFINED_REF Flags
	; DEFINED_REF_STORE_FILE		1b			0	; 
	; DEFINED_REF_RETRIEVE_FILE		10b			1	; 
	; DEFINED_REF_LETTERS			100b			2	; 
	; DEFINED_REF_REPLACE_LETTERS_LIST	1000b			3	; 
	; DEFINED_REF_SEPARATOR			10000b			4	; 
	; DEFINED_REF_RESTORE_FILE		100000b			5	; 
	; DEFINED_REF_RETRIEVE_FILE_FLOW	1000000b		6	; 
	; DEFINED_REF_STORE_FILE_LIST		10000000b		7	; 
	; DEFINED_REF_REPLACE_LETTERS_FLOW	100000000b		8	; 

	

section '.text' code readable writeable executable align 16


ref:
namespace ref
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
	add rcx, Ref.flowAlloc
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.ref
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.flags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.unprocessed
	mov rax, 1
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.paramCount
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.repIndex
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.valueAlloc
	mov rax, 0
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.listAlloc
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.definedRefFlags
	mov rax, 0
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.list
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, Ref.flowAlloc
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


end namespace