#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

char **shell_split(char *input){
	char ** words;
	words = malloc(4 * sizeof(char*));
	if(words == NULL)
		return NULL;
	size_t wordsIndex = 0;
	size_t wordsLen = 4;
	
	char *currentWord;
	
	//func has to know, if prev char was also space
	//initialised with 1, so that input with whitespace at the beginning
	//causes no error
	int prevCharIsSpace = 1;
	
	char currentChar;
	
	
	size_t inputLen = strlen(input);
	
	for(size_t i = 0; i < inputLen; i++){
		currentChar = input[i];
		//currentChar is space --> no action required, waiting for next letter
		if(isspace(currentChar)){
			//several consecutive whitespaces
			if(prevCharIsSpace)
				continue;
			
			//end of new word, new word has to be malloced and finished one has to be assigned to words
			else {
				prevCharIsSpace = 1;
				input[i] = '\0';
				//not enough space in words, one entry has to be reserved for NULL terminator
				//if (wordsIndex == wordsLen - 1) {
				//	words = realloc(words, wordsLen * 2 * sizeof(char *));
				//	if (words == NULL)
				//		return NULL;
				//	wordsLen *= 2;
				//}
				////insert currentWord into Words and inc wordsIndex
				//words[wordsIndex++] = currentWord;

			}
		}
		//letter found
		else{
			//beginning of new word
			if(prevCharIsSpace){
				prevCharIsSpace = 0;
				 //get new pointer to new beginning of word
				currentWord = input+i;
				//if words is not big enough, realloc double the space
				if (wordsIndex == wordsLen - 1) {
					words = realloc(words, wordsLen * 2 * sizeof(char *));
					if (words == NULL)
						return NULL;
					wordsLen *= 2;
				}
				//insert currentWord into Words and inc wordsIndex
				words[wordsIndex++] = currentWord;
			}


			
		}
	}
	
	//set terminating NULL-pointer in words array, catches case, if input only consists of whitespaces
	words[wordsIndex] = NULL;
	
	return words;
	
	
}