#ifndef MYUNISTD_H
#define MYUNISTD_H

#include "./mystddef.h"

struct mytimeval {
    long mtv_sec;  /* Sekunden */
    long mtv_usec; /* Mikrosekunden */
};

typedef struct myrusage {
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
} rusage;

ssize_t myread(int fd, void* buf, size_t count);
ssize_t mywrite(int fd, const void* buf, size_t count);
int myclose(int fd);
int mypipe(int fds[2]);
int mydup2(int oldfd, int newfd);
pid_t myfork(void);
int myexecve(const char *fn, char* const argv[], char* const envp[]);
pid_t mywait4(pid_t pid, int *st, int flags, struct myrusage *ru);
int mychdir(const char *dirname);
void myexit(int status);

#endif
