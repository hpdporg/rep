



section '.text' code readable writeable executable align 16



namespace processing
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
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processRetrieveFileFlow		
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processStoreFileList		
	add rsp, 8*8

	sub rsp, 8*8
	mov r9, [definedRefFlags]
	mov r8, [refRegistryAddr]
	mov rdx, [item]
	mov rcx, [parsingAddr]
	call processReplaceLettersFlow		
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


end namespace