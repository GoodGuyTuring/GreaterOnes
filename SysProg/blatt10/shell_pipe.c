#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include "mystdshell.h"



int run_cmdline(char** argv) {
	char* pipe_sym = "|";
	char* cd_sym = "cd";
	int **pipe_fds;
	int pipe_found = 0;
	int index = 0;
	int* pipe_ind;
	int pipe_cnt;
	pid_t wpid;
	pid_t pid;
	int child_status;
	int is_error = 0;
	
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
		
		if(pipe_fds == NULL)
			return -1;
		
		//create pairs of fds and pipes
		for(int j = 0; j < pipe_cnt; j++){
			pipe_fds[j] = malloc(2*sizeof(int));
			if(pipe_fds[j] == NULL)
				return -1;
			//prüfen, ob pipe erfolgreich
			if(mypipe(pipe_fds[j])< 0)
				return -1;
		}
		
		//create forked processes for each subcommand and configure pipe
		//TODO: close unneccessary fd's
		
		for(index = 0; index <= pipe_cnt; pipe_cnt++){
			//im kindProzess
			pid = fork();
			if(pid < 0)
				exit(-1);
			if(!pid){
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
		while((wpid = wait(&child_status)) > 0){
			if(child_status < 0)
				is_error = 1;
		}
		//free pipe_fds and pipe_ind
		for(int i = 0; i < pipe_cnt; i++){
			free(pipe_fds[i]);
		}
		free(pipe_fds);
		free(pipe_ind);
		if(is_error)
			return -1;
		return 0;
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