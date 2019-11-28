#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "shell.h"
#include "myunistd.h"
#include "mygetline.h"
#include "mystdlib.h"

extern char **environ;
char** shell_split(char* input);


void printErrorMsg(int msg) {
	char* message = malloc(4*sizeof(char));
	if (message == NULL) myexit(1);

	//Fehlermeldung auf STDERR ausgeben
	message = myinttostr(message, msg);
	mywrite(2, message, strlen(message));
	free(message);

	char* ch = "\n";
	mywrite(2, ch, 1);
}

void main(void) {

	while(1) {
		//$ auf STDERR ausgeben
		mywrite(2, "$ ", 2);						

		//Buffer für Eingabe
		size_t buflen = 8;
		char* buffer = malloc(buflen*sizeof(char));
		if (buffer == NULL) myexit(1);
		
		//Kommandozeile von STDIN einlesen
		ssize_t res = mygetline(&buffer, &buflen, 0);	

		//Beenden: EOF gelesen
		if (res == 0) myexit(0);

		//Fehlerwert auf STDERR ausgeben			
		if (res < 0) printErrorMsg(res);						
			
		//Input parsen
		char** splitted = shell_split(buffer);
		if (splitted == NULL) myexit(1);

		//Leeren Input ignorieren
		if (splitted[0] == NULL) {					
			free(buffer);
			free(splitted);
			continue;
		}

		//Befehl ausführen
		int runres = run_cmdline(splitted);

		//Fehlerwert auf STDERR ausgeben
		if (runres < 0)	printErrorMsg(runres);

		//Ressourcen freigeben
		free(splitted);
		free(buffer);
	}

}


char** shell_split(char* input) {

	//Speicher allokieren + Fehlerbehandlung
	char ** output = malloc(8 * sizeof(char*));
	if(output == NULL) return NULL;

	//Variablen
	char *word;				//Aktuelles Wort
	char current;				//Aktuelles zeichen
	size_t index = 0;			//Index des Wortes im Array
	size_t outputLen = 8;			//Anzahl Wörter im Array
	size_t inputLen = strlen(input);	//Länge des Input-Strings
	int lastSpace = 1;			//Merker, ob letztes Zeichen Leerzeichen
	size_t i = 0;				//Laufvariable

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
				int size = outputLen * 2 * sizeof(char *);
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
	if (no_fork) {				//Nicht forken
		return myexecve(*argv, argv, environ);
	} else {				//Forken
		pid_t pid = myfork();
		if (pid < 0) {			//Fehlerfall
			return -1;
		} else if (pid == 0) {		//Kindprozess
			myexecve(*argv, argv, environ);
		} else {			//Elternprozess
			return pid;
		}
	}
}

int run_cmdline(char** argv) {
	pid_t ret = run_command(argv, 0);

	if (ret > 0) { 				//Kindprozess-PID
		mywait4(ret, NULL, 0, NULL);	//Warten auf Beendigung des Kindprozesses
		return 0;
	} else {				//Fehlerfall
		return -1;
	}
}
