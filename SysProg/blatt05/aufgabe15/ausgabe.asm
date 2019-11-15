; Definition der externen glibc-Funktionen
global main

extern puts
extern fgets
extern stdin

SECTION .bss
buff: resw 21

; Daten-Segment           
SECTION .data

;Buffer für 20 ASCII-Zeichen
;buff: db `12345678901234567890`, 0
bufflen: db 21

; Text-Segment (Code)
SECTION .text
main:		; Parameter für fgets übergeben
		; Signatur: char *fgets(char *str, int n, FILE *stream)
		mov rdi, buff
		mov rsi, bufflen
		mov rdx, [stdin]
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
		;mov byte [buff+rcx], 'x'
schleife:	mov r8, [buff+rcx]				; Char laden
		add r8, 0
		jz ausgabe
		
		; Line Feed/Neue Zeile: 10

		cmp r8, 10
		jne weiter
		
		mov byte [buff+rcx], 32				; Zeilenumbruch durch Leerzeichen ersetzen
		jmp incCounter

weiter:		; Kleinbuchstaben: a (97) - 122 (z)
	
		cmp r8b, 'a'
		jl incCounter

		cmp r8b, 'z'
		jg incCounter

		sub r8, 32					; ToUpperCase()
		mov [buff+rcx], r8
		
incCounter:	inc rcx
		jmp schleife							
								; Sprungbedingung		
ausgabe:	; Parameter für puts übergeben
		; Signatur: int puts(const char *str)
		mov rdi, buff
		call puts					; Ausgabe in stdout per glibc-Aufruf

exit:		; ... Programm mit ErrorCode 0 beenden.
		mov	rax, 60 	; sys_exit
		mov	rdi, 0		; ErrorCode = 0
		syscall


