#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{    
	   char received_msg[150],sent_msg[150];
       struct sockaddr_in _server;
       int sock;

    bzero((char *) &_server, sizeof (_server));

    sock = socket(AF_INET, SOCK_STREAM, 0);

    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = inet_addr("127.20.100.1");
    _server.sin_port = htons(2244);

    connect(sock, (struct sockaddr *) &_server, sizeof (_server));
    printf("Write your message:\n");
	
	
	
    while(fgets(received_msg, 150 , stdin)!=NULL)
    {
      send(sock,received_msg,strlen(received_msg),0);

      if(recv(sock,sent_msg,150,0)==0)
          printf("No message found!!!");
      else
          fputs(sent_msg,stdout);

       bzero(sent_msg,150);
    }

  close(sock);
  return 0;
}