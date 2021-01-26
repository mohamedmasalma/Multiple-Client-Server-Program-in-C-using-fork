#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>


void *handle_conn(void *_sock){
    int received ,sock = *(int*)_sock;
    char _message[500];

      while((received=recv(sock,_message,500,0))>0)
      {
           send(sock,_message,received,0);
      }
      close(sock);

      if(received==0)
      {
        printf("Clinet has Disconnected");
      }
      else
      {
        perror("receiving failed");
      }
    return 0;
}
int main(int argc , char *argv[])
{
    int _sock , _client_address_port ,address_len, *sock_ptr;
    struct sockaddr_in address_port , client_address_port;

    _sock = socket(AF_INET , SOCK_STREAM , 0);

    address_port.sin_family = AF_INET;
    address_port.sin_addr.s_addr = INADDR_ANY;
    address_port.sin_port = htons( 3000 );



    bind(_sock,(struct sockaddr *)&address_port , sizeof(address_port)) ;


    listen(_sock , 5);


    printf("waiting for clients to connect...");
   address_len= sizeof(struct sockaddr_in);

       while(_client_address_port=accept(_sock,(struct sockaddr*)&client_address_port,(socklen_t*)&address_len))
       {

        printf("Client is ready to send messages.\n");
        pthread_t sniffer_thread;
        sock_ptr = malloc(1);
        *sock_ptr = _client_address_port;

        if( pthread_create( &sniffer_thread , NULL ,  handle_conn , (void*) sock_ptr) < 0)
        {
            perror("Problem while creating thread.");
            return 1;
        }

    }


    return 0;
}


