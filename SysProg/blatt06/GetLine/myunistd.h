#include "mystddef.h"
#ifndef _MYUNISTD_H_3
#define _MYUNISTD_H_3

struct mytimeval {
    long mtv_sec;  /* Sekunden */
    long mtv_usec; /* Mikrosekunden */
};

struct myrusage {
    struct mytimeval mru_utime; /* CPU-Zeit */
    struct mytimeval mru_stime; /* Kernel-CPU-Zeit */
    long mru_maxrss;   /* Maximales Resident Set Size in KiB */
    long mru_ixrss;    /* (nicht verwandt) */
    long mru_idrss;    /* (nicht verwandt) */
    long mru_isrss;    /* (nicht verwandt) */
    long mru_minflt;   /* Minor Faults (Seitenfehler ohne tatsächliche E/A) */
    long mru_majflt;   /* Major Faults (Seitenfehler mit E/A) */
    long mru_nswap;    /* (nicht verwandt) */
    long mru_inblock;  /* Anzahl an Dateisystem-Eingabe-Operationen */
    long mru_oublock;  /* Anzahl an Dateisystem-Ausgabe-Operationen */
    long mru_msgsnd;   /* (nicht verwandt) */
    long mru_msgrcv;   /* (nicht verwandt) */
    long mru_nsignals; /* (nicht verwandt) */
    long mru_nvcsw;    /* Voluntary Context Switches (vom Prozess erlaubt) */
    long mru_nivcsw;   /* Involuntary Context Switches (vom B.S. forciert) */
};

ssize_t myread(int fd, void *buf, size_t count);

ssize_t mywrite(int fd, const void *buf, size_t count);

int myclose(int fd);

int mypipe(int fds[2]);

int mydup2(int oldfd, int newfd);

pid_t myfork(void);

int myexecve(const char *file, char * const argv[], char * const envp[]);

pid_t mywait4(pid_t pid, int *st, int flags, struct myrusage *ru);

int mychdir(const char *pathname);

void myexit(int status);

#define	PROT_NONE	0x00	/* Kein Zugriff erlaubt. */
#define	PROT_READ	0x01	/* Speicher darf gelesen werden. */
#define	PROT_WRITE	0x02	/* Speicher darf beschrieben werden. */
#define	PROT_EXEC	0x04	/* Speicher darf ausgeführt werden. */

#define	MAP_SHARED	0x01	/* Shared Memory. */
#define	MAP_PRIVATE	0x02	/* Copy On Write. */
#define	MAP_FIXED	0x10	/* Verwende genau addr oder scheitere. */
#define	MAP_ANONYMOUS	0x20	/* Mapping ist nicht dateibasiert. */

void *mymmap(void *addr, size_t length, int prot, int flags, int fd,
             off_t offset);

void *mymremap(void *addr, size_t old_size, size_t new_size, int flags,
               void *new_addr);

int mymunmap(void *addr, size_t length);

/* mygetpid() und mykill() werden für myabort() gebraucht. */
pid_t mygetpid(void);

int mykill(pid_t pid, int sig);

#endif
