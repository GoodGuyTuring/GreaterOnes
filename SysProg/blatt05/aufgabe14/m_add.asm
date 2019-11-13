; Daten-Segment
%include "print.asm"
SECTION .data

; Text-Segment (Code)
SECTION .text

; Label öffentlich machen
global m_add

; Einsprungspunkt
m_add: 		; rdi 		; Zeilen
		; rsi		; Spalten
		  mov r9, rdx	; Anfang 1. Matrix
		  mov r10, rcx	; Anfang 2. Matrix
		; r8		; Anfang Ziel-Matrix

		; Bsp: [r10] Inhalt Speicherstelle 1. Matrix

		; rdi Zeilen mit rsi Einträgen
		; rdi*rsi Einträge insgesamt
		; Gesamtanzahl Matrixeinträge in rcx
		
		mov rax, rdi
		mul rsi
		mov rcx, rax 	; Gesamtanzahl Einträge
	
schleife:	mov r11, [r9]  ; Eintrag 1. Matrix
		add r11, [r10]	; + Eintrag 2.Matrix
		mov [r8], r11	; in 3. Matrix speichern
		
		; Matrix-Pointer weiterbewegen
		add r9, 8
		add r8, 8
		add r10, 8	
		
		
		loop schleife	; Schleife wiederholen
		ret	

