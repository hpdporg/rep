
extrn '__imp_newMatches' as newMatches:qword
extrn '__imp_processMatchFlags' as processMatchFlags:qword
extrn '__imp_getMatches' as getMatches:qword
extrn '__imp_lettersSame' as lettersSame:qword
extrn '__imp_lettersSameExact' as lettersSameExact:qword
extrn '__imp_getNextMatchIndex' as getNextMatchIndex:qword
extrn '__imp_hasMatch' as hasMatch:qword




	struc Matches
		label .
		.flags dq 0		; Matches flags
		.transformFlags dq 0	; Transform Flags
		.containsRangeList dq 0	; Contains or Range list (Contains X versus Range 0-200)
		.subRangeStartIndex dq 0	; Sub range start index
		.subRangeEndIndex dq 0	; Sub range end index
	end struc


	;Flags
	;MATCH_SUBRANGE_END_IND	MATCH_SUBRANGE_START_IND	MATCH_SUBRANGE	MATCH_TRANSFORM	MATCH_EVERY	MATCH_FIRST	MATCH_END	MATCH_START

	;Transform Flags
	;TRANSFORM_CONTAIN_OPTIONAL_COUNT	TRANSFORM_CONTAINS_SEQUENTIAL	TRANSFORM_ENDS_WITH	TRANSFORM_STARTS_WITH	TRANSFORM_CONTAINS_DISCONTINUOUS	TRANSFORM_EXCLUDES	TRANSFORM_CONTAINS	TRANSFORM_RANGE	TRANSFORM_INSENSITIVE_CASE



	struc MatchFlow
		label .
		.contains dq 0		; Contains flow
		.start dq 0		; Start match
		.end dq 0		; End match
		.firstMatch dq 0	; Contains first Match flow
		.everyMatch dq 0	; Contains every Match flow
		.matchIndexCount dq 0	; Required match index count minimum or maximum
		.startEndLength dq 0	; Start and ends matched i.e. length
	end struc



	; Used with address offsets
	virtual at 0
		Matches Matches
	end virtual

	; ---- Structures
	;element Element

	; Used with address offsets
	virtual at 0
		MatchFlow MatchFlow
	end virtual

	; ---- Structures
	;element Element