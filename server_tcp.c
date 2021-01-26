#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<WinSock2.h>
#include<conio.h>
#pragma comment(lib,"ws2_32.lib")
void *reciv(void * s){
puts("thread created");
SOCKET new_clinet=(SOCKET) s;
int reciv_size;
char message[2000];
while(1){
reciv_size = recv(new_clinet , message , 2000 , 0);
message[reciv_size]=NULL;
puts(message);
}
}
void main(){
 WSADATA wsa;
 SOCKET s , new_socket;
 struct sockaddr_in server , client;
    int c;
    char *message,server_reply[2000];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return;
    }

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 2222 );

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }

    puts("Bind done");

    //Listen to incoming connections
    listen(s , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
	pthread_t thread;
	while(1){
    new_socket = accept(s , (struct sockaddr *)&client, &c);
	puts("Connection accepted");
	pthread_create(&thread,NULL,reciv,(void *)new_socket);
	} 
    //Reply to client
    message = "Hello Client , I have received your connection. But I have to go now, bye\n";
    send(new_socket , message , strlen(message) , 0);

    getch();

    closesocket(s);
    WSACleanup();

    return;

}