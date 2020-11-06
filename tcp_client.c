#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h> 
int main() {
	int c_sock;
	c_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = inet_addr("40.88.2.46");
	

	if(connect(c_sock, (struct sockaddr*)&client, sizeof(client)) == -1) {
	printf("Connection failed");
	return 0;
	}
	
	char buff[100];

	while(1) {
		//Sending the message to Server
		printf("Enter the message to Server: ");
		gets(buff);
		write(c_sock, buff, sizeof(buff));
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		}

		//Receiving the message from Server
		int n = read(c_sock, buff, sizeof(buff));
		buff[n] = '\0';
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		}
		printf("Message from Server: %s\n", buff);
	}
	
	close(c_sock);
	return 0;
}
