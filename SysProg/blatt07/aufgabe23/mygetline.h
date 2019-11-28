#ifndef MYGETLINE_H
#define MYGETLINE_H
#include "mystdlib.h"
#include "myunistd.h"

ssize_t mygetline(char** buf, size_t* buflen, int fd);

#endif
