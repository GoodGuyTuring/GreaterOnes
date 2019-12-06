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

SECTION .data


SECTION .text

%macro feature 1
mov rax, %1
syscall
ret
%endmacro

myread: 	feature 0
mywrite:	feature 1
myclose:	feature 3
mypipe:		feature 22	
mydup2:		feature 33		
myfork: 	feature 57
myexecve:	feature 59
mywait4:	feature 61
mychdir: 	feature 80
myexit:		feature 30
