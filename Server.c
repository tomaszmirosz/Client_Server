/*
 ============================================================================
 Name        : server.c
 Author      : TM
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>												//dołączanie bibliotek
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "library.h" 											// dołączanie pliku nagłówkowego library.h

int main(int argc , char *argv[])
{
	char buf[50]; 												//deklaracja bufora
	int port = 8883;											// port domyślny
	if(argc == 2) {
		port = atoi(argv[1]);									//konwersja string na int
		printf("Port Introduced %d\n", port);
		if(port == 0) port = 8883;								//ustawienie portu domyślnego
	}

    int socket_desc , client_sock , c , read_size;				//definicja zmiennych typu int
    struct sockaddr_in server , client;							//definicja struktur dla klienta i serwera
    char message[100];											//definicja zmiennej char przechowywującej wiadomość od klienta


    socket_desc = socket(AF_INET , SOCK_STREAM , 0);			//stworzenie gniazda
    if (socket_desc == -1)
    {
        printf("Cannot create a socket");
    }
    puts("Socket created");										//gniazdo poprawni utworzone


    server.sin_family = AF_INET;								//ipv4
    server.sin_addr.s_addr = INADDR_ANY;						//bindowanie do wszystkich dostępnych interfejsów serwera
    server.sin_port = htons( port );							//host to network short


    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) //bindowanie połączenia
    {

        perror("Bind failed. Error");							//bindowanie nieudane
        return 1;
    }
    puts("Bind successfull");									//bindowanie udane


    listen(socket_desc , 3);									//oczekiwanie na połączenie


    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);


    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("Accept failed");								//połączenie nieudane
        return 1;
    }
    puts("Connected");


    while( (read_size = recv(client_sock , message , 100 , 0)) > 0 )
    {															//odebranie wiadomości
    	function(message, buf);
    	write(client_sock , buf , strlen(buf));
    }

    if(read_size == 0)
    {
        puts("Client disconnected");							//rozłączenie klienta
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("Receivinng failed");							//odbiór nieudany
    }

    if(!close(client_sock)) puts("Client socket closed"); 		//zamknięcie gniazda
    if(!close(socket_desc)) puts("socket desc closed");

    return EXIT_SUCCESS;
}

