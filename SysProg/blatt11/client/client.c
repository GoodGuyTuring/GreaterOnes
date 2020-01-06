#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>


int main(void){
	char send_buff[128];
	struct sockaddr_in server_add;
	char eingabe[128];
	short unsigned port;
	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_fd < 0){
		printf("error");
		exit(1);
	}
	
	server_add.sin_family = AF_INET;
	
	printf("\nBitte geben Sie die IP ein: ");
	scanf("%s", eingabe);
	server_add.sin_addr.s_addr = inet_addr(eingabe);
	
	printf("\nBitte geben Sie einen Port ein: ");
	scanf("%d", &port);
	server_add.sin_port = htons(port);
	
	while(1){
		printf("\nBitte geben Sie eine Nachricht ein: ");
		scanf("%s", send_buff);
		if(sendto(socket_fd, send_buff, sizeof(send_buff), 0, &server_add, sizeof(server_add)) < 0){
			printf("Fehler beim Empfangen der Nachricht!, beenden...");
			exit(1);
		}
	}
	
}