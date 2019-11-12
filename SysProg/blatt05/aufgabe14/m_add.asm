; Daten-Segment
SECTION .data

; Text-Segment (Code)
SECTION .text

; Label öffentlich machen
global m_add

; Einsprungspunkt
m_add: 		; rdi 		; Zeilen
		; rsi		; Spalten
		; rdx		; Anfang 1. Matrix
		  mov r9, rcx	; Anfang 2. Matrix
		; r8		; Anfang Ziel-Matrix

		; Bsp: [rdx] Inhalt Speicherstelle 1. Matrix

		; rdi Zeilen mit rsi Einträgen
		; rdi*rsi Einträge insgesamt
		; Gesamtanzahl Matrixeinträge in rcx

		mov rax, rdi
		mul rsi
		mov rcx, rax 	; Gesamtanzahl Einträge
	
schleife:	mov r11, [rdx] ; Eintrag 1. Matrix
		add r11, [r9]	; + Eintrag 2.Matrix
		mov [r8], r11	; in 3. Matrix speichern

		; Matrix-Pointer weiterbewegen
		inc rdx
		inc r8
		inc r9 	
		
		loop schleife	; Schleife wiederholen
		ret	

