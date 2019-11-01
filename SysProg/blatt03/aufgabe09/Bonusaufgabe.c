#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char* argv[]){
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	srand(time(0));
	
	for(int i=0;i<a;i++){
		for(int j = 0;j<b;j++){
			printf("%d",rand()%11);
			if(j<b-1){
				printf(",");
			}
		}
		if(i<a-1){
			printf(";");
		}
	}
}
