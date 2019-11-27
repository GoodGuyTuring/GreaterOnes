#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myunistd.h"

int main(int argc, char** argv) {
	//Abbruch: Zu wenig Parameter
	if (argc < 2) myexit(1);

	//Parameter
	int count = atoi(argv[1]);
	char* name = argv[2];
	
	//Parameterliste für Kindprozesse
	char** args = malloc((argc - 1)*sizeof(char*));
	if (args == NULL) myexit(1);

	//Erster Parameter: Aufgerufenes Programm
	args[0] = argv[2];

	//Alle weiteren Kommandozeilenargumente
	int j=1;
	for(;j<argc-1;j++) {
		args[j] = argv[j+2];
	}	
	
	//Array NULL-terminieren
	args[j] = NULL;
	
	//Kind-Prozesse forken
	pid_t pid;

	for(int i=0;i<count;i++) {
		pid = myfork();
		
		if (pid < 0) {				//Fehlerfall			
			myexit(1);
		} else if (pid == 0) {			//Innerhalb des Kind-Prozesses
			execvp(name, args);		//Prozesskontext überschreiben
		}
	}
	
	//Parameterliste freigeben
	free(args);
}
