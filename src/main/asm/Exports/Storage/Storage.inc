extrn '__imp_newStorage' as newStorage:qword
extrn '__imp_defineRecordPath' as defineRecordPath:qword
extrn '__imp_retrieve' as retrieve:qword
extrn '__imp_storeLetters' as storeLetters:qword
extrn '__imp_restoreLetters' as restoreLetters:qword
extrn '__imp_retrieveRecordNames' as retrieveRecordNames:qword
extrn '__imp_retrieveRecordNamesExtension' as retrieveRecordNamesExtension:qword
extrn '__imp_removeRecord' as removeRecord:qword
extrn '__imp_debugNum' as debugNum:qword
extrn '__imp_debugLetters' as debugLetters:qword
extrn '__imp_debugNumMsg' as debugNumMsg:qword
extrn '__imp_debugLettersMsg' as debugLettersMsg:qword


	struc Record
		label .
		.allocAddr dq 0		; Binary or text allocation addr
		.allocSize dq 0		; Size of allocation (base 8)
		.name dq 0		; Record name with extension
		.location dq 0		; Path
		.builtLocation dq 0	; Built Path
		.handle dq 0
		.allocFlags dq 0	; STORAGE_ALLOC_FLAGS Alloc can be combination, i.e. List/Flow of Letters
		.jDelimiter dq 0	; Vertical, line delimiter (i.e. newline)
		.iDelimiter dq 0	; Horizontal, column delimiter (i.e. comma or tab in csv)
	end struc



	; Used with address offsets
	virtual at 0
		Record Record
	end virtual

	; ---- Structures
	;element Element
