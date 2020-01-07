#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void){
	printf("Test");
	int sock_fd, err;
	struct sockaddr_in server_addr;
	struct sockaddr_in tmp_addr;
	socklen_t sock_len = sizeof(tmp_addr);
	
	char recv_buffer[128];
	
	struct sockaddr_in recv_addr;
	socklen_t recv_sock_len = sizeof(recv_addr);
	
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0){
		printf("error");
		exit(1);
	}
	//socket mit AF_INET, zufälligem port und eigener ip adresse initialisieren
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(0);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	err = bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));
	if(err<0){
		printf("error");
		exit(1);
	}
	//host port auf stdout ausgeben
	getsockname(sock_fd, (struct sockaddr *)&tmp_addr, &sock_len);
	printf("Ich bin ein Server, mein Port ist: %d", ntohs(tmp_addr.sin_port));
	fflush(stdout);
	
	//recvfrom-loop wartet immer auf nachrichten und gibt diese aus
	while(recvfrom(sock_fd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*) &recv_addr, &recv_sock_len) >= 0){
		printf("Nachricht von Client erhalten! \nIP: %s \nHostname: TODO \nPort: %d \n\nNachricht:\n%s",
		inet_ntoa(recv_addr.sin_addr) ,ntohs(recv_addr.sin_port),recv_buffer);
		fflush(stdout);
	}
	close(sock_fd);
	//todo close
	return 0;
}
