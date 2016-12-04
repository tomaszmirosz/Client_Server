/*
 ============================================================================
 Name        : Client.c
 Author      : TM
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>								//dodawanie blibliotek
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
    int sock;										// stworzenie zmiennej sock
    struct sockaddr_in server;						// stworzenie struktury posiadającej informacje o serwerze
    char operation[100] , score[200];				// zmienne przechowujące dane o wyniku i operacjach
    char *address= "127.0.0.1";						//adres serwera
    int port = 8883;								// port


printf( "address = %s\n", address );
printf("port: %d\n",port );



    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)									//nie mozna utworzyć gniazda
    {
        printf("Can not open a socket");
    }
    puts("Socket created");							// gniazdo zostało stworzone

    server.sin_addr.s_addr = inet_addr(address);		//adres przypisany do interfejsu
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Not connected");					// nie połączono
        return 1;
    }

    puts("Connected\n");							// połączono

    while(1)
    {
        printf("Type operation : 'number'<space>'sign'<space>'number'");	// podanie liczb oraz dziłania
        printf("Example:");
        printf("    5 + 5 \n");
        fgets( operation, sizeof(operation),stdin);



        if( send(sock , operation , strlen(operation) , 0) < 0)
        {
            puts("Sending failed");					// wysyłanie nieudane

            return 1;
        }



        if( recv(sock , score , 200 , 0) < 0)
        {
            puts("Receivinng failed");   			//odbieranie nieudane
            break;
        }

        puts("SCORE :");							//wynik
        puts(score);
        memset(score,0,strlen(score));				// resetowanie wyniku
    }

    close(socket);									// zamknięcie gniazda

    return 0;
}
# Client_Server
# Client_Server Server.c library.c library.h
