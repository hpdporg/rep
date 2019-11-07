extrn '__imp_newStorage' as newStorage:qword
extrn '__imp_defineRecordPath' as defineRecordPath:qword
extrn '__imp_retrieve' as retrieve:qword
extrn '__imp_storeLetters' as storeLetters:qword
extrn '__imp_restoreLetters' as restoreLetters:qword
extrn '__imp_retrieveRecordNames' as retrieveRecordNames:qword




	struc Record
		label .
		.allocAddr dq 0		; Binary or text allocation addr
		.allocSize dq 0		; Size of allocation (base 8)
		.name dq 0		; Record name with extension
		.location dq 0		; Path
		.builtLocation dq 0	; Built Path
		.handle dq 0
	end struc




	; Used with address offsets
	virtual at 0
		Record Record
	end virtual

	; ---- Structures
	;element Element
