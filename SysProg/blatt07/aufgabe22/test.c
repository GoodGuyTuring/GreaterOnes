#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int forked = 0;
	pid_t pid;
	int status;

	if (argc < 2) return 0;

	//Parameter
	int count = atoi(argv[1]);
	int name = argv[1];

	for(int i=0;i<count;i++) {
		if (pid = fork() < 0) {			//Kind-Prozess forken
			puts("Fork Error!");
			exit(1);
		} else if (pid == 0) {			//Innerhalb des Kind-Prozesses
			execvp(name, argv);
		} else {				//Innherhalb des Parent-Prozesses
			while (wait(&status) != pid)	//Wait for Completion
               		;
		}
	}
		
}
