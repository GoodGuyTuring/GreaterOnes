#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

//Globaler Server-Kontostand
int kontoStand = 0;

//Programm beenden
void die() {
	printf("Fehler aufgetreten.\n"); 
	printf("Fehlercode :	%i\n", errno);
	printf("Programm wurde beendet ***\n");
	exit(1);
}

int main(int argc, char** argv){
	//Nicht genug Parameter: Portnummer fehlt
	if (argc != 2) die();

	//Benötigte Variablen für den Server
	int listener_fd, connection_fd;
	struct sockaddr_in server_addr, client_addr;
	int addrlen = sizeof(struct sockaddr);
	char buffer[128];
	
	//Port ermitteln
	int port = atoi(argv[1]);
	if (port == 0) die();
	
	//Listening Socket initialisieren	
	listener_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listener_fd < 0) die();

	//Socketaddresse initialisieren
	server_addr.sin_family = AF_INET;			//Internet
	server_addr.sin_port = htons(port);			//Portnummer
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//IP-Adresse, zufällig
	
	//Listening Socket an Sockadresse binden
	int err = bind(listener_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));
	if (err < 0) die();

	//Listening Socket für Verbindungsaufbau passiv schalten
	if (listen(listener_fd, 5) == 0) {			//Auf Verbindung warten
		while(1) {
			//Verbindungsanfrage akzeptieren,
			//wir erhalten Connection Socket
			connection_fd = accept(listener_fd, (struct sockaddr *) &client_addr, (socklen_t*)&addrlen);
			if (connection_fd < 0) die();

			//Befehle vom Socket bearbeiten
			do {
				sprintf(buffer, "%i", kontoStand);
				write(connection_fd, buffer, 128);
				
				//Befehl in Buffer einlesen
				ssize_t recv = read(connection_fd, buffer, 128);

				if (recv > 0) {			//Befehl empfangen

					//Input Negativ: Abheben, Positiv: Einzahlen
					int result = atoi(buffer);
					kontoStand += result;
					printf("Neuer Kontostand: %i\n", kontoStand);

				} else if (recv < 0) {		//Fehlerfall
					die();
				} else {			//Verbindungsabbau
					close(connection_fd);
					break;
				}

			} while (1);
			
		}

	} else {	//Fehlerfall
		die();
	}

	//Listening Socket schließen
	close(listener_fd);
	return 0;
}
