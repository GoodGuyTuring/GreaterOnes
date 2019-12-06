#ifndef MYGETLINE_H
#define MYGETLINE_H
#include "../stdlib/mystdlib.h"
#include "../syscalls/myunistd.h"

ssize_t mygetline(char** buf, size_t* buflen, int fd);

#endif
