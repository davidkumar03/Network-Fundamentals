#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int client_sock;
	struct sockaddr_in server_addr;
	socklen_t addrlen=sizeof(server_addr);
    char buffer[1024]= {0};
	char *client_msg="I am Client!!!";
	client_sock=socket(AF_INET,SOCK_DGRAM,0);
	if(client_sock==-1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_port = 3500;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(server_addr.sin_zero),'\0',8);
	sendto(client_sock,client_msg,strlen(client_msg),0,(struct sockaddr*)&server_addr,addrlen);
	printf("Message sent: %s\n",client_msg);
	int recv_msg=recvfrom(client_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,&addrlen);
	printf("Received Meassge: %s\n",buffer);
	close(client_sock);
	return 0;
}

