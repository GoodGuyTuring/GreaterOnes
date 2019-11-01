;macht die Funktionen global sichtbar 
global myread
global mywrite
global myclose
global mypipe
global mydup2
global myfork
global myexecve
global mywait4
global mychdir
global myexit

;Daten
SECTION .data

;Code
SECTION .text

;Makro für Systemaufrufe mit syscall nummer als parameter
%macro sysmakro 1
mov rax, %1
syscall
ret
%endmacro

;Funktionsdefinition mit zugehörigen syscall argumenten
myread: 	sysmakro 0
mywrite:	sysmakro 1
myclose:	sysmakro 3
mypipe:		sysmakro 22	
mydup2:		sysmakro 33		
myfork: 	sysmakro 57
myexecve:	sysmakro 59
mywait4:	sysmakro 61
mychdir: 	sysmakro 80
myexit:		sysmakro 30
