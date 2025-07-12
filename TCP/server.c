#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int sockfd,new_sockfd;
	struct sockaddr_in my_addr;
	socklen_t addrlen = sizeof(my_addr);
    char buffer[1024] = {0};
	char *serv_msg="I am a Sever!!!";
	sockfd=socket(AF_INET,SOCK_STREAM,0);//socket creation
	if(socket==-1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
    }
    my_addr.sin_family=AF_INET;
	my_addr.sin_port = 3500;  // port number
    my_addr.sin_addr.s_addr =inet_addr("127.0.0.1");  // 127.0.0.1
	memset(&(my_addr.sin_zero),'\0',8);
    if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0)//bind specific oprt and ip address
	{
		perror("Bind Failed");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	if(listen(sockfd,1)<0) // listen the incoming connection
	{
		perror("Listen falied");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
    printf("Server listening on 127.0.0.1...\n");
    new_sockfd=accept(sockfd,(struct sockaddr*)&my_addr,&addrlen); //conncet with client
	if (new_sockfd < 0) {
        perror("accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
	printf("Client connected.\n");
	int recv_msg=recv(new_sockfd,buffer,sizeof(buffer),0);  //recieve message
	if(recv_msg > 0)
	{
		 printf("Received: %s\n", buffer);
		 send(new_sockfd,serv_msg,strlen(serv_msg),0);  //send a  message
	}
	close(new_sockfd);  //close
	close(sockfd);     //close
	return 0;
}
