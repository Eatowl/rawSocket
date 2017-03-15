#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <resolv.h>
#include <string.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/epoll.h>

#define QUEUE_LENGTH 1
#define MAX_BUF 256

int main() {
	int server_socket;
	struct sockaddr_in saddr, caddr;
	char *buf;
	server_socket = socket(PF_INET, SOCK_DGRAM, 0);
	printf("server_socket %d\n", server_socket);
	buf = (char *) malloc(MAX_BUF);
	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(server_socket, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
		perror("bind() error");
		close(server_socket);
		exit(1);
	}
	socklen_t client_len;
	while (1) {
		client_len = sizeof(caddr);
		if (recvfrom(server_socket, buf, MAX_BUF, 0, (struct sockaddr *) &caddr, &client_len) < 0) {
			perror("recvfrom() error");
			close(server_socket);
			exit(1);
		}
		strcat(buf, "_serv");
		if (!strcmp(buf, "exit")) break;
		if (sendto(server_socket, buf, strlen(buf), 0, (struct sockaddr *) &caddr, client_len) < 0) {
			perror("sendto() error");
			close(server_socket);
			exit(1);
		}
	}
	free(buf);
	close(server_socket);
	return 0;
}