#ifndef _MYSTDLIB_H
#define _MYSTDLIB_H

#include "mystddef.h"

// Laut C-Standard wird abort() in stdlib.h definiert.
#include "myabort.h"

void *mymalloc(size_t size);

void *mycalloc(size_t nmemb, size_t size);

void *myrealloc(void *ptr, size_t size);

void myfree(void *ptr);

#endif