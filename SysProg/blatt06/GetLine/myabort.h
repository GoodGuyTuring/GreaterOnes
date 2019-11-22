/* An einigen Stellen wo keine andere Fehlerindikation möglich ist (d.i. in
 * arena_delete()) wird myabort() verwandt; ohne die Bonusaufgabe ist es
 * nicht notwendig. */

#ifndef _MYABORT_H
#define _MYABORT_H

#ifndef MYABORT_NO_NORETURN
#define NORETURN __attribute__((__noreturn__))
#endif

void myabort(void) NORETURN;

#endif