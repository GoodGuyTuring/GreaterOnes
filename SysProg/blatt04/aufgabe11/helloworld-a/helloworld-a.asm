; Daten-Segment
SECTION .data

; String der Länge eines Bytes definieren
str:	db `Hello world!\n`
; Länge des Strings in strlen speichern
; $: aktuelle Position
; str: Startposition des Strings
; equ $ - str ist daher die Länge des Strings
strlen: equ $ - str

;define quarter: Zahl ins Datensegment ablegen
num:	dq 1337

; Text-Segment (Code)
SECTION .text

; Label öffentlich machen
global _start

; Einsprungspunkt
_start:
	; Hello World!\n auf Standardausgabe ausgeben...
	mov	rax, 1 		; sys_write
	mov	rdi, 1 		; Filedeskriptor für Standardausgabe stdout
	mov	rsi, str 	; Buffer: Auszugebender String
	mov	rdx, strlen 	; Länge des buffers
	syscall

	; ... Programm mit ErrorCode 0 beenden.
	mov	rax, 60 	; sys_exit
	mov	rdi, 0		; ErrorCode = 0
	syscall
