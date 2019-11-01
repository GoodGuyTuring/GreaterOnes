#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int palindrom_check1(const char *st1) {
int st1_len = strlen(st1), i;
for(i = 0; i < st1_len / 2; i++)
if (toupper(st1[i]) != toupper(st1[st1_len -i-1])) return 0;
return 1;
}
int main(void) {
char *st1, *st2;
int st1_len, i;
char *exit = "exit";
st1 = malloc(100);
if(st1 == NULL){
	return -1;
}
st2 = malloc(100);
if(st2 == NULL){
	return -1;
}
printf("Zum Beenden exit als Eingabe angeben. \n");
while (1) {
printf("Eingabe: ");
scanf("%s", st1);
if (strcmp(st1, exit) == 0) {
	free(st1);
	free(st2);
	return 0;
}
st1_len = strlen(st1);
for (i=0; i<st1_len; i++) {
st2[i] = toupper(st1[st1_len -1 -i]);
}
st2[i] = '\0';
if (palindrom_check1(st1)) printf("1. Test: Palindrom \n");
else printf("1. Test: Kein Palindrom \n");

for (int j = 0; j < st1_len; j++){
	st1[j]= toupper(st1[j]);
}
if (!strcmp(st1, st2)) printf("2. Test: Palindrom\n");
else printf("2. Test: Kein Palindrom\n");
}
free(st1);
free(st2);
return 0;
}