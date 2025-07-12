#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	
	int client_sock;
	struct sockaddr_in serv_addr;
	char *msg="Hello,David!!!";
    char buffer[1024] = {0};
	client_sock=socket(AF_INET,SOCK_STREAM,0);//socket creation
	if(client_sock==-1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
    }
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port = 3500;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	if(connect(client_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
	{
		perror("Connection falied");
		close(client_sock);
		exit(EXIT_FAILURE);
	}
	send(client_sock,msg,strlen(msg),0);
	printf("Message sent: %s\n", msg);
	int read=recv(client_sock,buffer,sizeof(buffer),0);
	printf("Received from server: %s\n", buffer);
    close(client_sock);
	return 0;
}
