/* https://www.binarytides.com/server-client-example-c-sockets-linux */

/*
 C ECHO client example using sockets
 */
#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr

int main(int argc, char *argv[]) {
	int sock;
	struct sockaddr_in server;
	int slen = sizeof(server);
	char server_reply[2000];

	char *string = "{\"color\" : \"BLUE\", \"x\" : 1, \"y\" : 150, \"shapesize\" : 3}";

	//Create socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("192.168.56.3");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);


	//Send the json data
	printf("Send Data\n");
	if (sendto(sock, string, strlen(string), 0, (struct sockaddr *)&server, slen) < 0) {
		puts("Send failed");
		return 1;
	}

	//Receive the reply from the server
	printf("Wait for Data\n");
	if (recvfrom(sock, server_reply, 2000, 0,(struct sockaddr *)&server, &slen) < 0) {
		puts("recv failed");
	}

	puts("Server reply :");
	puts(server_reply);


	close(sock);
	return 0;
}
