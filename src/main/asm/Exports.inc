extrn '__imp_ExitProcess' as ExitProcess:qword

extrn '__imp_GetProcessHeap' as GetProcessHeap:qword
extrn '__imp_GetLastError' as GetLastError:qword

extrn '__imp_HeapAlloc' as HeapAlloc:qword
extrn '__imp_HeapFree' as HeapFree:qword

include 'Exports/Parsing.inc'
include 'Exports/Ref.inc'
include 'Exports/RunCycles.inc'
include 'Exports/Allocate.inc'
include 'Exports/List.inc'
include 'Exports/Letters.inc'
include 'Exports/Storage/Storage.inc'
include 'Exports/Storage/StorageFlow.inc'
include 'Exports/Storage/StorageLetters.inc'
include 'Exports/Storage/StorageList.inc'
include 'Exports/Matching.inc'
include 'Exports/Replacement.inc'
include 'Exports/Processing.inc'
include 'Exports/ProcessItem.inc'
