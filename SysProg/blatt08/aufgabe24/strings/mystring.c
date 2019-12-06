#include "mystring.h"
#include "mystddef.h"

/*
Misst die Länge eines Strings (ohne Nullbyte)
*/
size_t mystrlen(char* str) {
	//Rückgabewert mit 0 initialisieren
	size_t res = 0;

	/*String *str durchlaufen, 
	  bis bei Nullbyte angekommen
	*/
	while(*str != 0) {
		//Dabei Rückgabewert hochzählen
		res++;
		str++;
	}
	
	//String-Länge zurückgeben
	return res;
		
}

/*
*/
char *mystrcpy(char *dest, const char *src) {
	//Startposition des Zielstrings merken
	char* anfang = dest;
	
	//Quellstring durchlaufen, bis Nullbyte
	while(*src != 0) {
		//Zeichenweise kopieren (Quelle => Ziel)
		*dest = *src;
		
		//Pointer für Quell und Zielstring hochzählen
		dest++;
		src++;
	}
	
	//Zielstring mit Nullbyte terminieren!
	*dest = 0;
	
	//Adresse des ersten Zeichens des Zielstrings zurückgeben
	return anfang;
}

/*
*/
char* mystrcat(char *dest, const char *src) {
	char* ret = dest;
	
	while(*dest != 0) {
		dest++;
	}
	
	while(*src != 0) {
		*dest = *src;
		src++;
		dest++;
	}
	
	return ret;
}

/*
*/
int mystrcmp(const char *s1, const char *s2) {
	int res = 0;
	
	while(res == 0) {
		if(*s1 == 0 && *s2 == 0) return 0;
		
		if(*s1 < *s2) return -1;
		if(*s1 > *s2) return 1;
		
		s1++;
		s2++;
	}
	
	return 0;	
}

/*
*/
void *mymemcpy(void *dest, const void *src, size_t n) {
	int i = 0;

    char* destchar = (char*)dest;
    char* srcchar = (char*)src;
	
	for(i=0;i<n;i++) {
		destchar[i] = srcchar[i];
	}

	return dest;
}

/*
*/
void *mymemset(void *buf, int ch, size_t n) {
	int i = 0;
	
	char* bufchar = (char*)buf;
	
	for(i=0;i<n;i++) {
		*(bufchar + i) = (char)ch;
	}
	
	return buf;
}
