#ifndef _MYSTDDEF_H_3
#define _MYSTDDEF_H_3

typedef long ssize_t;
typedef int pid_t;
typedef unsigned long size_t;

#define NULL ((void*)0)
/* CHAR_BIT wird in mystdlib.c für u.A. mycalloc() verwandt. */
#define CHAR_BIT 8

typedef long off_t;

#endif