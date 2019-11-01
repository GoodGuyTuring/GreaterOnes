
#include "mystring.h"
#include <stdio.h>


int main(){
	setbuf(stdout, NULL);
	printf("Hello World\n");
	char a[100];
	char b[100];
	printf("Bitte String eingeben: ");
	scanf("%s",a);
	printf("String: %s\n",a);
	size_t len = mystrlen(a);
	printf("Länge des Strings: %i\n",(int)len);
	mystrcpy(b,a);
	printf("Copy vom String: %s\n",b);
	mystrcat(b,a);
	printf("CAT vom String: %s\n",b);
	int x = mystrcmp(a,b);
	printf("%i\n",x);
	return 0;
}
