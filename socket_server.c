#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define HOST "192.168.1.4"
#define PORT 7373


int main() {

	// Important Variables
	int sock_fd, client, reuse_flag = 1;
	struct sockaddr_in addr;

	// Buffer to send and recieve data accross the client and the server.
	char recvBuffer[1024];
	char sendBuffer[512] = "Message from a sample socket server\n";

	// Creating the socket file descriptor
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(HOST);

	socklen_t addr_len = sizeof(addr);

	// adding reuseaddr in socket options
	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (const char*)&reuse_flag, sizeof(int));

	// Binding the socket
	bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr));

	// Listening
	printf("[+] Listening for incomming connections...");
	listen(sock_fd, 3);

	// Accept request from the client
	client = accept(sock_fd, (struct sockaddr *)&addr, &addr_len);

	// Sending and receiving data across server and client
	printf("Client connected successfully...\nSending data...\n");
	send(client, sendBuffer, sizeof(sendBuffer), 0);
	recv(client, recvBuffer, sizeof(recvBuffer), 0);

	printf("Message from the client: %s\n", recvBuffer);	// Printing out the recvBuffer
	printf("Done.\n");


	return 0;
}
