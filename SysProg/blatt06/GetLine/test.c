#include <stdio.h>
#include <stdlib.h>
#include "mygetline.h"
#define stdin 1

int main(void) {

	//Speicher allokieren
	char* buffer = malloc(8*sizeof(char));
	char** bufptr = &buffer;
	size_t buflen = 8;

	//Zeichen aus stdin in Buffer schreiben
	mygetline(bufptr, &buflen, stdin);
	
	//Buffer ausgeben
	if (*bufptr != NULL) printf("\n\n%s", *bufptr);

	//Speicher freigeben
	if (buffer != NULL) free(buffer);

}
