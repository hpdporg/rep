extrn '__imp_newList' as newList:qword
extrn '__imp_newLastItem' as newLastItem:qword
extrn '__imp_getNextItem' as getNextItem:qword
extrn '__imp_getLastDivergedItem' as getLastDivergedItem:qword
extrn '__imp_getLastDivergedItemNesting' as getLastDivergedItemNesting:qword
extrn '__imp_getNextItemNesting' as getNextItemNesting:qword
extrn '__imp_getConvergedItemCount' as getConvergedItemCount:qword
extrn '__imp_getNextTangentItem' as getNextTangentItem:qword
extrn '__imp_nextItemNesting' as nextItemNesting:qword
extrn '__imp_lastItemNesting' as lastItemNesting:qword
extrn '__imp_resetIndex' as resetIndex:qword
extrn '__imp_newNextItem' as newNextItem:qword
extrn '__imp_getPriorItem' as getPriorItem:qword
extrn '__imp_getNextItemMatch' as getNextItemMatch:qword
extrn '__imp_getNextItemMatchComp' as getNextItemMatchComp:qword




	struc ListItem
		label .
		.item dq 0
		.previous dq 0
		.nesting dq 0
		.next dq 0
	end struc

	struc ItemMatch
		label .
		.item dq 0
		.index dq 0
		.nesting dq 0
	end struc

	struc List
		label .
		.firstItem dq 0
		.listSize dq 0
		.itemsCount dq 0
		.index dq 0
		.indexItem dq 0 			; Address of item at current index for faster item retrieval
		.indexedItemIndex dq 0			; Used to determine if index was set manually or actually equals indexed Item address
		.itemMatch dq 0				; Item matching
	end struc	
	


	; Used with address offsets
	virtual at 0
		ListItem ListItem
	end virtual

	; Used with address offsets
	virtual at 0
		ItemMatch ItemMatch
	end virtual


	; Used with address offsets
	virtual at 0
		List List
	end virtual


	; ---- Structures
	;list List


	;newSVGMsg db 'New SVG',0
	