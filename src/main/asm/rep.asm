include 'format/format.inc'


format MS64 COFF

include 'Exports.inc'


public start as 'start'

section '.data' data readable writeable align 16

	val7h db 0


section '.text' code readable writeable executable align 16


;align 16
start:
       push rbp
       mov rbp, rsp
       and rsp, -32
       sub rsp, 8*12;8;7;8;9
       and rsp, -32


	 mov rcx, 0
	 sub rsp, 8*4
	 call [ExitProcess]
	 add rsp, 8*4