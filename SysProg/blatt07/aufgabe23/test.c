#include <stdio.h>
#include <stdlib.h>
#include "mystdlib.h"
#include <math.h>

int main(void) {

	char* teststr = malloc(10 * sizeof(char));
	if (teststr == NULL) return 0;
	
	teststr = "-15732";

	int* test = malloc(sizeof(int));
	if (test == NULL) return 0;

	mystrtoint(teststr, test);
	printf("mystrtoint:	%i\n", *test);
	
	char* testy = malloc(7*sizeof(char));
	if (testy == NULL) return 0;

	testy = myinttostr(testy, *test);
	printf("myinttostr:	%s\n", testy);
	
	free(testy);
	free(test);
	
}
