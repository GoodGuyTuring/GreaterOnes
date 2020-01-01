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
	char* pipe_sym = "|";
	char* cd_sym = "cd";
	int **pipe_fds;
	int pipe_found = 0;
	int index = 0;
	int* pipe_ind;
	int pipe_cnt;
	pid_t wpid;
	
	//1: prüfen, ob | als einzelnes Wort in der Eingabe vorkommt, falls ja, wird pipe_split aufgerufen
	char* current_word = argv[index];
	
	while(current_word != NULL){
		if(strcmp(current_word, pipe_sym) == 0){
			pipe_found = 1;
			break;
		}
		current_word = argv[++index];
	}
	
	//pipe_split aufrufen, wenn pipe vorhanden
	if(pipe_found){
		//wrong positioning of pipe symbols
		if((pipe_ind = pipe_check(argv, &pipe_cnt)) == NULL)
			return -1;
		
		//create enough pairs of file descriptors for pipes
		pipe_fds = malloc(pipe_cnt*sizeof(int*));
		
		//create pairs of fds and pipes
		for(int j = 0; j < pipe_cnt; j++){
			pipe_fds[j] = malloc(2*sizeof(int));
			pipe(pipe_fds[j]);
		}
		
		//create forked processes for each subcommand and configure pipe
		//TODO: close unneccessary fd's
		
		for(index = 0; index <= pipe_cnt; pipe_cnt++){
			//im kindProzess
			if(!fork()){
				//erster command vor pipe
				if(index == 0){
					dup2(pipe_fds[0][1], 1);
					//close fd's
					for(int i = 0; i < pipe_cnt; i++){
						if(i == 0){
							close(pipe_fds[index][0];
						}
						else{
							close(pipe_fds[index][0];
							close(pipe_fds[index][1];
						}
					}
					run_command(argv, 1);
					
				}
				//letzter command nach einer pipe
				else if(index == pipe_cnt){
					dup2(pipe_fds[index-1][0], 0);
					//close fd's
					for(int i = 0; i < pipe_cnt; i++){
						if(i == pipe_cnt-1){
							close(pipe_fds[i][1];
						}
						else{
							close(pipe_fds[i][0];
							close(pipe_fds[i][1];
						}
					}
					run_command(argv+pipe_ind[pipe_cnt-1]+1, 1);
				}
				//command in mitte einer pipe
				else{
					dup2(pipe_fds[index-1][0], 0);
					dup2(pipe_fds[index][1], 1);
					//close fd's
					for(int i = 0; i < pipe_cnt; i++){
						if(i == index-1){
							close(pipe_fds[i][1];
						}
						else if(i == index){
							close(pipe_fds[i][0];
						}
						else{
							close(pipe_fds[i][0];
							close(pipe_fds[i][1];
						}
					}
					run_command(argv+pipe_ind[index-1]+1, 1);
				}
			}
		}
		//wait for alle children to finish
		while((wpid = wait(NULL)) > 0){
			
		}
		//free pipe_fds and pipe_ind
		for(int i = 0; i < pipe_cnt; i++){
			free(pipe_fds[i]);
		}
		free(pipe_fds);
		free(pipe_ind);
	}
	//sonst normaler aufruf
	else{
		if (mystrcmp(cd_sym, *argv) == 0) {
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
	
	
}

int* pipe_check(char **argv, int* count){
	/*
	recievec array of strings, NULL terminated, that contains a pipe;
	checks if pipe positions are legitimate for example nothing like "| command " or " | |" etc.
	returns int array with indices of pipes and number of pipes in count if split successful
	else returns NULL, and number of pipes in count
	replaces pipe symbols with NULL
	the returned array must be freed after use
	*/

	int word_index = 0;
	char *current_word = argv[word_index];
	int* pipe_ind;
	*count = 0;
	//no pipe as first word
	if(strcmp(current_word, "|") == 0 || current_word == NULL)
		return NULL;
	
	pipe_ind = malloc(4*sizeof(int));
	int ind_len = 4;
	current_word = argv[++word_index];
	
	//fangen mit zweitem wort in argv in der schleife an
	while(current_word != NULL){
		//schauen, ob jetziges wort pipe
		if(strcmp(current_word, "|") == 0){
			//wenn wort vorher pipe war steht dort jetzt NULL, nicht erlaubt
			if(argv[word_index-1] == NULL){
				free(pipe_ind);
				return NULL;
			(*count)++;
			//mehr speicher allokieren
			if(count > ind_len){
				pipe_ind = realloc(pipe_ind, 2*ind_len*sizeof(int));
				ind_len *= 2;
			}
			//index von pipe_symbol eintragen
			pipe_ind[(*count)-1] = word_index;
			//setze pipe auf null
			argv[word_index] = NULL;
		}
		current_word = argv[++word_index];
	}
	
	//schauen, das letztes wort keine pipe
	if(strcmp(argv[word_index-1], "|") == 0){
		free(pipe_ind);
		return NULL;
	}
	
	return pipe_ind;
	
}