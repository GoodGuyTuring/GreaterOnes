; Definition der externen glibc-Funktionen
global main



; Daten-Segment           
SECTION .data

;Buffer für 20 ASCII-Zeichen
buff: db `12345678901234567890`, 0
bufflen: equ $ - buff

; Text-Segment (Code)
SECTION .text

extern puts
extern fgets
extern stdin

main:		; Parameter für fgets übergeben
		; Signatur: char *fgets(char *str, int n, FILE *stream)
		mov rdi, buff
		mov rsi, bufflen
		mov rdx, stdin
									; Filedeskriptor 0 ist stdin
		; Einlesen von stdin per glibc-Aufruf
		call fgets

		; Ergebnis nach Aufruf in buff
		; Prüfung ob Returnwert NULL	
		add rax, 0						
		jz exit

		; String-Manipulation:
		; ToUpper + Kein Zeilenumbruch	+ Nullterminieren!
		
		; Über String laufen
		mov rcx, 0
		
schleife:	mov r8, [buff+rcx]				; Char laden
		jz weiter
		
		; Line Feed/Neue Zeile: 10

		cmp r8, 10
		jne weiter1
		mov r9, buff
		mov byte [buff+rcx], 32				; Zeilenumbruch durch Leerzeichen ersetzen

weiter1:	; Kleinbuchstaben: a (97) - 122 (z)
		cmp r8, 97
		jb incCounter

		cmp r8, 122
		ja incCounter

		sub r8, 32					; ToUpperCase()
		mov [buff+rcx], r8
		
incCounter:	add rcx, 1
		jmp schleife							
								; Sprungbedingung		
weiter:		; Parameter für puts übergeben
		; Signatur: int puts(const char *str)
		mov rdi, buff
		
		call puts					; Ausgabe in stdout per glibc-Aufruf

exit:		; ... Programm mit ErrorCode 0 beenden.
		mov	rax, 60 	; sys_exit
		mov	rdi, 0		; ErrorCode = 0
		syscall


