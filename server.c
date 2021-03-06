#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{ 
	int welcomeSocket, newSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(PF_INET,SOCK_STREAM,0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);

	serverAddr.sin_addr.s_addr = inet_addr("192.168.253.131");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
	bind(welcomeSocket, (struct sockaddr *)&serverAddr,sizeof(serverAddr));
	 
	if(listen(welcomeSocket,2)==0)
	{
		printf("Listening\n");

		addr_size = sizeof serverStorage;
		newSocket = accept(welcomeSocket, (struct sockaddr *)&serverStorage, &addr_size);

		strcpy(buffer,"Hello Client\n");
		send(newSocket,buffer,13,0);
		return 0;
	}
}
