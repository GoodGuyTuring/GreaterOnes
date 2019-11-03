; Daten-Segment
SECTION .data

; String der Länge eines Bytes definieren
str:	db `Hello world!\n`

; Länge des Strings in strlen speichern
; $: aktuelle Position
; str: Startposition des Strings
; equ $ - str ist daher die Länge des Strings
strlen: equ $ - str

;Buffer auf 10 ASCII-Zeichen limitiert
strzahl: db `                                                                                `
strzahllen: equ $ - strzahl

;define quarter: Zahl ins Datensegment ablegen
num:	dq 1337133713

; Text-Segment (Code)
SECTION .text

; Label öffentlich machen
global _start

;Makro für sys_write
%macro write 3
	mov rax, 1	; sys_write
	mov rdi, %1	; Filedeskriptor
	mov rsi, %2	; Buffer: Auszugebender String
	mov rdx, %3	; Länge des Buffers
	syscall
%endmacro

; Einsprungspunkt
; Hello World!\n auf Standardausgabe ausgeben...
_start:		write 1, str, strlen	

		mov eax, num		; Auszugebende Zahl wird in eax übergeben
		call printnumber	; Funktion aufrufen

		; ... Programm mit ErrorCode 0 beenden.
		mov	rax, 60 	; sys_exit
		mov	rdi, 0		; ErrorCode = 0
		syscall

printnumber:	mov r13, [eax]		; Wert von num nach r13 sichern
		mov r8, strzahl		; r8 ist Pointer in Buffer Array
		add r8, strzahllen	; r8 zeigt ans Ende des Buffers

		; Wiederholtes Teilen und rückwärts Anhängen des Restes an den Buffer
_loop:		mov rax, r13		; r13 nach rax kopieren
		mov rdx, 0		; Restliche Daten für Division
		mov rcx, 10		; Durch 10 teilen
		div rcx			; Dividieren

		mov r13, rax		; Ergebnis wieder nach r13
		mov r10, rdx		; Rest nach r10

		add r10, 48		; Rest in RDX zu ASCII
		sub r8, 8		; 1 Char nach links im Buffer
		mov [r8], r10		; Rest in Buffer schreiben
		
		add r13, 0		; Zero-Flag aktualisieren
		
		jnz _loop

		; Buffer auf Standardausgabe ausgeben
		write 1, strzahl, strzahllen

		ret

