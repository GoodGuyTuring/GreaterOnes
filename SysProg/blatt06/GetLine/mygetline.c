#include <stdio.h>
#include <stdlib.h>
#include "mystddef.h"
#include "mystdlib.h"
#include "mystddef.h"
#include "myunistd.h"

ssize_t mygetline(char** buf, size_t* buflen, int fd) {

	int counter = 0;	//Gesamtzahl gelesene Zeichen

	//Fehler abfangen
	if ((buf == NULL) || (*buf == NULL)) {	
		char* storage = malloc(8*sizeof(char));
		if (storage == NULL) return -1;
		buf = &storage;
	}

	//Fehler abfangen
	if ((buflen == NULL) || (*buflen <= 0)) {
		size_t* len = malloc(sizeof(size_t));
		if (len == NULL) return -1;
		*len = 8;
		buflen = len;
	}

	char* buf_old = *buf;	//Pointer sichern

	while(1) {
		//Anzahl gelesener Zeichen
		ssize_t read = myread(fd, *buf, 1);
		
		//Dynamisch vergrößern
		if (counter > *buflen) {
			puts("\n\nRealloc");
			int newsize = 2 * (*buflen) * sizeof(char);	//Neue Buffer-Größe
			*buf = realloc(buf_old, newsize);
			if (*buf == NULL) return -1;			//Realloc-Fehler
			
			buf_old = *buf;					//Neuen Pointer sichern
			*buf = (*buf) + counter; 			//Offset addieren
			
			*buflen = (*buflen) * 2;			//Bufferlänge verdoppeln
		}

		//Gelesenes Zeichen
	
		char val = **buf;
	
		int chval = (int)val;
		
		//Debug Info
		printf("\nInput: %i\tCounter: %i\tBuflen: %zu", chval, counter, *buflen);

		//Gesamtzahl Zeichen hochzählen
		counter++;

		//Abbruchbedingungen
		if(read < 0) break;					//Fehler oder EOF
		if (chval == 10) break; 				//Zeilenumbruch
		
		//Nächstes Zeichen setzen
		*buf = (*buf) + 1;
	}

	//Nullterminieren
	*buf = 0;

	//Pointer auf String-Anfang zurücksetzen
	*buf = buf_old;

	return counter;

}


