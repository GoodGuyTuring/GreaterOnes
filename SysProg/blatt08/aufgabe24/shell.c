#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include "shell.h"
#include "syscalls/myunistd.h"
#include "syscalls/mystddef.h"
#include "getline/mygetline.h"
#include "stdlib/mystdlib.h"
#include "strings/mystring.h"

extern char **environ;

void printErrorMsg(int msg) {
	char* message = malloc(8*sizeof(char));
	if (message == NULL) myexit(1);

	//Fehlermeldung auf STDERR ausgeben
	message = myinttostr(message, msg);
	mywrite(2, message, mystrlen(message));
	free(message);

	char* ch = "\n";
	mywrite(2, ch, 1);
}

void execute(char* buffer) {
	//Input parsen
	char** splitted = shell_split(buffer);
	if (splitted == NULL) myexit(1);

	//Leeren Input ignorieren
	if (splitted[0] != NULL) {		
		//Befehl ausführen
		int runres = run_cmdline(splitted);

		//Fehlerwert auf STDERR ausgeben
		if (runres < 0)	printErrorMsg(runres);

	}

	free(splitted);
}

int main(void) {
	char* buffer = NULL;

	while(1) {
		//Prompt auf STDERR ausgeben
		mywrite(2, "$ ", 2);

		//Buffer-Länge
		size_t buflen = 8;

		//Buffer allokieren
		buffer = malloc(buflen * sizeof(char));
		if (buffer == NULL) return 1;
		
		//Kommandozeile von STDIN einlesen 
		ssize_t res = mygetline(&buffer, &buflen, 0);	

		if (res < 0) {
			printErrorMsg(res);	//Fehlerwert auf STDERR ausgeben 
		} else {
			execute(buffer);	//Ausführen
		}					
		
		//Ressourcen freigeben	
		free(buffer);		
	}

	return 1;
}

char** shell_split(char* input) {

	//Speicher allokieren + Fehlerbehandlung
	char** output = malloc(8 * sizeof(char*));
	if(output == NULL) return NULL;

	//Variablen
	char *word;				//Aktuelles Wort
	char current;				//Aktuelles zeichen
	size_t index = 0;			//Index des Wortes im Array
	size_t outputLen = 8;			//Anzahl Wörter im Array
	size_t inputLen = mystrlen(input);	//Länge des Input-Strings
	int lastSpace = 1;			//Merker, ob letztes Zeichen Leerzeichen
	size_t i = 0;				//Laufvariable

	mymemset(output, 0, outputLen);

	for(i = 0; i < inputLen; i++){
		current = input[i];

		if(isspace(current)){
			//Leerzeichen: Auf nächsten Buchstaben warten
			
			//Mehrere Leerzeichen hintereinander
			if(lastSpace) continue;
			
			//Ende des aktuellen Wortes
			//Terminiere bzw. schneide String an dieser Stelle
			lastSpace = 1;
			input[i] = 0;

		} else if (lastSpace) {
			//Buchstabe gefunden: Beginn eines neuen Wortes
			lastSpace = 0;

			//Beginn des Wortes
			word = input+i;

			//Dynamisch vergrößern: Verdoppeln, falls zu klein
			//inklusive Fehlerbehandlung
			if (index == outputLen - 1) {
				int size = outputLen * 2 * sizeof(char*);
				output = realloc(output, size);

				if (output == NULL) return NULL;

				outputLen *= 2;		
			}

			//Word an Liste anhängen + danach Index inkrementieren
			output[index++] = word;
			
		}
	}
	
	//Terminierender NULL-Pointer: 
	//Falls Input nur aus Leerzeichen besteht
	output[index] = NULL;
	return output;
	
}

pid_t run_command(char** argv, int no_fork) {
	if (no_fork) {						//Nicht forken
		return myexecve(*argv, argv, environ);
	} else {						//Forken
		pid_t pid = myfork();

		if (pid < 0) {					//Fehlerfall
			return -1;
		} else if (pid == 0) {				//Kindprozess
			myexecve(*argv, argv, environ);
			printErrorMsg(-1);			//Fehlerfall
			kill(getpid(), SIGUSR1);
			return -1;		
		} else if (pid > 0) {				//Elternprozess
			return pid;
		}
	}
}

int run_cmdline(char** argv) {
	char* c = "cd";

	if (mystrcmp(c, *argv) == 0) {
		if (argv[1] == NULL) return -1;
		return mychdir(argv[1]);
	}

	pid_t ret = run_command(argv, 0);

	if (ret > 0) { 					//Kindprozess-PID
		struct myrusage* usage = malloc(sizeof(struct myrusage));
		if (usage == NULL) myexit(1);

		mywait4(ret, NULL, 0, usage);		//Warten auf Beendigung des Kindprozesses
		free(usage);
		return 0;
	} else {					//Fehlerfall
		return -1;
	}
}
