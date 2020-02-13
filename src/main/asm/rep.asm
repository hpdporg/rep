
include 'format/format.inc'


format MS64 COFF

include 'Exports.inc'


include 'rep.inc'



public startRep as 'startRep'

section '.data' data readable writeable align 16

	dataSecInitVal2 db 0						; Define arbitrary value. Placeholder if this section is needed.
	


section '.text' code readable writeable executable align 16


align 16
startRep:
       push rbp
       mov rbp, rsp
       and rsp, -32
       sub rsp, 8*12;8;7;8;9
       and rsp, -32



	sub rsp, 8*8
	call runCycles.new
	add rsp, 8*8
	
	mov rdx, newlineWinLetters	;newlineUnixLetters
	mov [newlineLetters], rdx


	sub rsp, 8*12
	mov rcx, rax
	call runCycles.begin
	add rsp, 8*12

	
	 mov rcx, 0
	 sub rsp, 8*4
	 call [ExitProcess]
	 add rsp, 8*4