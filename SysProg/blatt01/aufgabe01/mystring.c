#include "mystring.h"
#include "mystddef.h"
#include <stdio.h>
#include <stdlib.h>

size_t mystrlen(const char *str) {
	//const sorgt dafür, dass Inhalt nicht verändert wird
	// geht string bis 0 Byte durch und inkrementiert count
	size_t count = 0;
	while (*str) {
		count++;
		str += 1;
	}
	return count;
}

char* mystrcpy(char *dest, const char *src) {
	//int src_size = ((int) mystrlen(src)) + 1;
	//geht src string bis zum 0 byte durch und kopiert Inhalt nach dest
	//setzt am Ende noch Nullbyte
	unsigned i;
	for (i = 0; src[i]; i++) {
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return dest;

}

char* mystrcat(char *dest, const char *src) {
	//konkateniert src an dest, durch mystrcpy auf postion des 0 Bytes
	mystrcpy(dest + mystrlen(dest), src);
	return dest;
}

int mystrcmp(const char *s1, const char *s2) {
	// vergleicht s1 mit s2 durch Schleifen durchlauf solange Strings gleich sind
	unsigned i;
	for (i = 0; s1[i] == s2[i]; ++s1, ++s2) {
		if (!s1[i] && !s2[i]) {
			return 0;
		}
	}
	// wenn strings ungleich werden die ersten jeweils ungleichen Buchstaben verglichen
	if((unsigned char)s1[i]<(unsigned char)s2[i]){
		return -1;
	}
	else{
		return 1;
	}
}
