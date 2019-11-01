#include "mystddef.h"

//Wrapper-Funktionen
struct myrusage;
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
