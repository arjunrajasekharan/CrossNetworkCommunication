#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h> 
int main() {
	int s_sock, c_sock;
	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server, other;
	memset(&server, 0, sizeof(server));
	memset(&other, 0, sizeof(other));
	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;
	socklen_t add;
	

	if(bind(s_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
		printf("Binding failed\n");
		return 0;
	}
	
	
	if(listen(s_sock, 10) != 0) {
		printf("Listen Unsuccessful\n");
		return 0;
	}
	add = sizeof(other);
	c_sock = accept(s_sock, (struct sockaddr*)&other, &add);
	if(c_sock < 0) {
		printf("Failed to accept\n");
		return 0;
	}

	char buff[100];

	while(1) {
		//Receiving the message from Client
		int n = read(c_sock, buff, sizeof(buff));
		buff[n] = '\0';
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		}
		printf("Message from Client: %s\n", buff);
		
		//Sending the message to Client
		printf("Enter the message to Client: ");
		gets(buff);
		write(c_sock, buff, sizeof(buff));
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		}
	}
	
	close(c_sock);
	close(s_sock);
	return 0;
}
