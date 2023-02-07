#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char message[200];
	if(argc < 3){
	fprintf(stderr, "usage %s hostname port\n", argv[0]);
	exit(1);
}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	error("Error on creating socket");

	server = gethostbyname(argv[1]);
	if(server == NULL)
	{
	fprintf(stderr, "Error, no such host");
}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr , (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	error("connection failure");


	char *buffer = argv[3];
	n = write(sockfd, buffer, strlen(buffer));

	if(n < 0)
	error("error on sending command line argument i.e roll no.");

	n = read(sockfd, message, 200);
	if(n < 0)
	error("Error on reading socket");

	if(strcmp(message, "Invalid user") == 0){
	printf("%s", message);
	}else{
	printf("%s\n", message);
	bzero(message, 200);
	}
	char reply[10] = "Thank You";

	write(sockfd, reply, strlen(reply));
	bzero(reply, 10);

	char replyMsg[100];
	read(sockfd, replyMsg, 100);
	printf("%s",replyMsg);
	bzero(replyMsg, 100);

while(1)
{
	char temp[10];
	fgets(temp, 10, stdin);
	write(sockfd, temp, strlen(temp));

	if(strcmp(temp, "quit\n") == 0)
	break;

	bzero(temp, 10);

	read(sockfd, message, 200);
	printf("\n%s\n", message);
	bzero(message,200);
	printf("\nDo you want to see your information again? (Type again)\n");

}

	close(sockfd);
	return 0;
}
