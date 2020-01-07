#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
//Checks Endianness of system
//Returns 1 if Little Endian, 0 if Big Endian

int is_big_endian(void)
{
	int x = 1;
	char* c = &x;
	if(*c)
		return 0;
	return 1;
}

char* my_inet_ntoa(struct in_addr in)

{
	//interpret Ipv4-adress as 32bit uint
	unsigned int addr = *(unsigned int *) &in;
	char *result = malloc(16*sizeof(char));
	unsigned char bytes[4];

	for(int i = 0; i < 4; i++){
		if(is_big_endian()) {
			//big endian
			printf("big endian");
			bytes[3-i] = (addr >> (i *8)) & 0xFF;
		} else {
			//little endian
			bytes[i] = (addr >> (i *8)) & 0xFF;
		}
	}
	snprintf(result, 16, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
	return result;
	
}

int main(void) {
	struct in_addr test;
	struct addrinfo** result;
	char eingabe[100];
	char host[100];
	char serv[100];
	test.s_addr = 138571950;
	printf("%s\n", my_inet_ntoa(test));
	printf("%s\n", inet_ntoa(test));
	if(is_big_endian()){
		printf("System ist big endian");
	}
	else{
		printf("system ist little endian");
	}

	printf("bitte geben Sie einen hostnamen ein: ");
	scanf("%s", eingabe);

	getaddrinfo(eingabe, NULL, NULL, result);
	struct sockaddr_in*  tmp= result[0]->ai_addr;
	printf("%s\n", inet_ntoa(tmp->sin_addr));
	freeaddrinfo(*result);
	
	printf("Bitte geben Sie eine IP adresse ein: ");
	scanf("%s", eingabe);
	struct sockaddr_in tmp_add;
	tmp_add.sin_family = AF_INET;
	//struct in_addr tmp_in_add;
	inet_pton(AF_INET, eingabe, &tmp_add.sin_addr);
	//printf("%i\n", tmp_in_add.s_addr);
	//tmp_add.in_addr = tmp_in_add;

	getnameinfo((struct sockaddr*)&tmp_add, sizeof(tmp_add), host, sizeof(host), NULL, 0, 0);
	printf("\n%s\n", host);
	 

}
