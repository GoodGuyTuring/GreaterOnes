#include <stdlib.h>
#include <stdio.h>
#include "../syscalls/mystddef.h"
#include "../syscalls/myunistd.h"
#include "../stdlib/mystdlib.h"
#include "../strings/mystring.h"

ssize_t mygetline(char** buf, size_t* buflen, int fd) {
	char* buffer = *buf;
	
	/*//Fehler abfangen
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
	}*/

	//Gesamt-Anzahl gelesener Zeichen
	ssize_t counter = 0;
	mymemset(buffer, 0, (*buflen));	//Buffer clearen

	while(1) {
		//Dynamisch vergrößern
		if (counter > (*buflen) - 1) {
			int newsize = 2 * (*buflen) * sizeof(char);	//Neue Buffer-Größe

			*buf = realloc(*buf, newsize);
			if (*buf == NULL) return -1;			//Realloc-Fehler
			buffer = *buf;

			*buflen = (*buflen) * 2;			//Bufferlänge verdoppeln
			mymemset(buffer+counter, 0, (*buflen)-counter);
		}

		if (myread(fd, buffer+counter, 1) == 0) break;

		//Gelesenes Zeichen
		char val = buffer[counter];
		int chval = (int)val;
		
		//Gesamtzahl Zeichen hochzählen
		counter++;

		//Abbruchbedingungen
		if (chval == 10) break; 				//Zeilenumbruch
	}

	//Nullterminieren
	buffer[counter] = 0;

	return counter;

}


