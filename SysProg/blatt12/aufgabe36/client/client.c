#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

//Programm beenden
void die() {
	printf("Fehler aufgetreten.\n"); 
	printf("Fehlercode :	%i\n", errno);
	printf("Programm wurde beendet ***\n");
	exit(1);
}

int main(int argc, char** argv){
	//Nicht genug Parameter: IP-Adresse/Portnummer fehlt
	if (argc != 3) die();
	
	//Benötigte Variablen für den Client
	char buffer[128];
	struct sockaddr_in server_addr;
	int addrlen = sizeof(struct sockaddr_in);
	
	//Server Socket initialisieren
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0) die();
	
	//Port ermitteln
	int port = atoi(argv[2]);
	if (port == 0) die();
	
	//Socketaddresse initialisieren
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(port);
	
	//Verbindung zu Server herstellen
	int err =  connect(socket_fd, (struct sockaddr *)&server_addr, addrlen);
	if (err < 0) die();

	while(1) {
		//Kontostand empfangen und ausgeben
		int res = read(socket_fd, buffer, 128);
		if (res < 0) {
			die();
		} else if (res > 0) {
			printf("Aktueller Kontostand: %s ,- EUR\n", buffer);
		} else {
			close(socket_fd);
			break;
		}

		//Transaktion übermitteln
		printf("\nBitte geben Sie eine Transaktion ein: ");
		int input = 0;
		if (scanf("%i", &input) != 1) die();
		sprintf(buffer, "%i", input);

		int res2 = write(socket_fd, buffer, sizeof(buffer));
		if (res2 < 0) die();
		
	}
	
}
