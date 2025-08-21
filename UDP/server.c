#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int server_sock;
	struct sockaddr_in my_addr;
	socklen_t addrlen=sizeof(my_addr);
    char buffer[1024]= {0};
	char *serv_msg="I am Server!!!";
	server_sock=socket(AF_INET,SOCK_DGRAM,0);
	if(server_sock==-1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	my_addr.sin_family=AF_INET;
	my_addr.sin_port = 3500;
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(my_addr.sin_zero),'\0',8);
	if(bind(server_sock,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0)
	{
		perror("Bind failed");
		close(server_sock);
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in client_addr;
	socklen_t addrlen2=sizeof(client_addr);
	int recv_msg=recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&addrlen2);
	if(recv_msg > 0)
	{
		printf("received Message: %s\n",buffer);
		sendto(server_sock,serv_msg,strlen(serv_msg),0,(struct sockaddr*)&client_addr,addrlen2);
	}
//	close(server_sock);
	return 0;
}


