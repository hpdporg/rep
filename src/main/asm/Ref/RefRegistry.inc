


section '.data' data readable writeable align 16


	struc RefRegistry
		label .
		.list dq 0		; Delimiter being used between rep items
		.definedList dq 0	; List of defined refs 
	end struc


	

	; Used with address offsets
	virtual at 0
		RefRegistry RefRegistry
	end virtual

	; ---- Structures
	;element Element


	gettingNextRegisteredRefValueMsg db 'Getting next Registered Ref Value..',0
	gettingNextRegisteredDefinedRefMsg db 'Getting next Registered Defined Ref..',0	
	

section '.text' code readable writeable executable align 16


refRegistry:
namespace refRegistry
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
	add rcx, RefRegistry.definedList
	add rcx, 1000b

	sub rsp, 8*4
	mov r8, rcx		
	mov rdx, 000001000b
	mov rcx, [heapAddress]
	call [ HeapAlloc] 
	mov [handleAllocatedMemory], rax
	add rsp, 8*4




	mov rbx, [handleAllocatedMemory]
	add rbx, RefRegistry.list
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
	mov [rbx], rax
	mov rbx, [handleAllocatedMemory]
	add rbx, RefRegistry.definedList
	sub rsp, 8*8
	call [newList]
	add rsp, 8*8
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

newLastRegisteredRef:
namespace newLastRegisteredRef
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label matches qword at rbp-40
	label refRegistryAddr qword at rbp-48
	label newRef qword at rbp-56
	label ref qword at rbp-64
	label refIndex qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [refRegistryAddr], rcx
	mov [ref], rdx	
	mov [refIndex], r8

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
	;mov [lettersIndex], rcx		; Begin as 0

	mov rbx, [ref]
	add rbx, Ref.repIndex
	mov r8, [refIndex]
	mov [rbx], r8

	
	sub rsp, 8*8
	mov rbx, [refRegistryAddr]
	add rbx, RefRegistry.list
	mov rcx, [rbx]
	call [resetIndex]
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [ref]
	mov rbx, [refRegistryAddr]
	add rbx, RefRegistry.list
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8





	mov rax, 0;[parsedLetters]



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


newLastRegisteredDefinedRef:
namespace newLastRegisteredDefinedRef
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*9);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label parsing qword at rbp-24 
	label matchIndex qword at rbp-32
	label matches qword at rbp-40
	label refRegistryAddr qword at rbp-48
	label newRef qword at rbp-56
	label ref qword at rbp-64
	label lettersIndex qword at rbp-72
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [refRegistryAddr], rcx
	mov [ref], rdx	
	
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
	;mov [lettersIndex], rcx		; Begin as 0


	

	sub rsp, 8*8
	mov rdx, [ref]
	mov rbx, [refRegistryAddr]
	add rbx, RefRegistry.definedList
	mov rcx, [rbx]
	call [newLastItem]
	add rsp, 8*8





	mov rax, 0;[parsedLetters]



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



; Existing Ref returned when exists, 0 when non-existent, 1 when defined match
; Takes Ref.ref not ref address as second param
getRegisteredRef:
namespace getRegisteredRef
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*10);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label definedList qword at rbp-32
	label matches qword at rbp-40
	label refRegistryAddr qword at rbp-48
	label nextRef qword at rbp-56
	label ref qword at rbp-64
	label lettersIndex qword at rbp-72
	label repIndex qword at rbp-80
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [refRegistryAddr], rcx
	mov [ref], rdx	
	mov [repIndex], r8


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
	mov [nextRef], rcx		; Begin as 0


	mov rbx, [refRegistryAddr]
	add rbx, RefRegistry.list
	mov r8, [rbx]
	mov [list], r8

	mov rbx, [refRegistryAddr]
	add rbx, RefRegistry.definedList
	mov r8, [rbx]
	mov [definedList], r8
	
	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [definedList]
	call [resetIndex]
	add rsp, 8*8


	nextItem:
	mov rbx, [list]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endList

	mov rcx, 0
	mov [nextRef], rcx		; Begin as 0


	sub rsp, 8*8
	mov rcx, gettingNextRegisteredRefValueMsg
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8

	sub rsp, 8*8
	mov rdx, [ref]
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [lettersSameExact]
	add rsp, 8*8
	cmp rax, 0
	je nextItem

	mov rax, [nextRef]


	mov rbx, [nextRef]	
	add rbx, Ref.flags
	mov rdx, [rbx]
	cmp rdx, 100b					;REF_DEFINED
	jne completed			; Found, already exists


	mov rbx, [nextRef]
	add rbx, Ref.repIndex
	mov rdx, [rbx]
	mov rcx, [repIndex]
	cmp rcx, rdx
	jne nonExistentDefinedRef	; New defined ref


	jmp completed			; Found, already exists



	endList:

	nextDefinedItem:
	mov rbx, [definedList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl completed

	mov rcx, 0
	mov [nextRef], rcx		; Begin as 0


	sub rsp, 8*8
	mov rcx, gettingNextRegisteredDefinedRefMsg
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rcx, [definedList]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	sub rsp, 8*8
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	;call [debugLettersMsg]
	add rsp, 8*8


	sub rsp, 8*8
	mov rdx, [ref]
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [lettersSameExact]
	add rsp, 8*8	
	cmp rax, 0
	je nextDefinedItem







	; return ref instead of 1?
	; how are we determining processed versus not?
	nonExistentDefinedRef:
	mov rax, 1b
	mov [nextRef], rax			; 1 when defined

	



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

; used when we need the defined ref's flags
getRegisteredDefinedRef:
namespace getRegisteredDefinedRef
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*10);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label definedList qword at rbp-32
	label matches qword at rbp-40
	label refRegistryAddr qword at rbp-48
	label nextRef qword at rbp-56
	label ref qword at rbp-64
	label lettersIndex qword at rbp-72
	label repIndex qword at rbp-80
	;virtual at rbp-64
	;	.list List
	;end virtual	


	mov [refRegistryAddr], rcx
	mov [ref], rdx	
	mov [repIndex], r8


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
	mov [nextRef], rcx		; Begin as 0



	mov rbx, [refRegistryAddr]
	add rbx, RefRegistry.definedList
	mov r8, [rbx]
	mov [definedList], r8

	sub rsp, 8*8
	mov rcx, [definedList]
	call [resetIndex]
	add rsp, 8*8




	nextDefinedItem:
	mov rbx, [definedList]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl completed

	sub rsp, 8*8
	mov rcx, [definedList]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax

	sub rsp, 8*8
	mov rdx, [ref]
	mov rbx, [nextRef]
	add rbx, Ref.ref
	mov rcx, [rbx]
	call [lettersSameExact]
	add rsp, 8*8	
	cmp rax, 0
	je nextDefinedItem


	mov rax, [nextRef]
	mov [nextRef], rax			; lettersSameExact returns 1 when defined

	




	;.completed:

	mov rax, [nextRef]
	completed:;dbg


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


unprocessedRefsCount:
namespace unprocessedRefsCount
	push rbp 
	mov rbp, rsp 
	sub rsp, (8*10);+(8*6)

	;mov rcx, [rbp+8] 
	;mov rdx, [rbp+12] 
	label heapAddress qword at rbp-8  
	label handleAllocatedMemory qword at rbp-16
	label list qword at rbp-24 
	label definedList qword at rbp-32
	label matches qword at rbp-40
	label refRegistryAddr qword at rbp-48
	label nextRef qword at rbp-56
	label ref qword at rbp-64
	label count qword at rbp-72
	label repIndex qword at rbp-80
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


	mov rcx, 0
	mov [count], rcx		; Begin as 0



	mov rbx, [refRegistryAddr]
	add rbx, RefRegistry.list
	mov r8, [rbx]
	mov [list], r8

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8




	nextItem:
	mov rbx, [list]
	mov rdx, rbx
	add rbx, List.index
	add rdx, List.itemsCount
	mov rcx, [rbx]
	mov r8, [rdx]
	cmp rcx, r8
	jnl endItems

	sub rsp, 8*8
	mov rcx, [list]
	call [getNextItem]
	add rsp, 8*8
	mov [nextRef], rax


	mov r10, [nextRef]
	add r10, Ref.unprocessed
	mov r11, [r10]
	cmp r11, 0
	jne nextItem
	
	mov rcx, [count]
	add rcx, 1b
	mov [count], rcx


	jmp nextItem
	
	endItems:

	sub rsp, 8*8
	mov rcx, [list]
	call [resetIndex]
	add rsp, 8*8




	completed:

	mov rax, [count]


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
;
;


end namespace