#include "mystddef.h"

size_t mystrlen(char *str);
char* mystrcpy(char *dest, const char *src);
char* mystrcat(char *dest, const char *src);
int mystrcmp(const char *s1, const char *s2);
void* mymemcpy(void *dest, const void *src, size_t n);
void* mymemset(void *buf, int ch, size_t n);