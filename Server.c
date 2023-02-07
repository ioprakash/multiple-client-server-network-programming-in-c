#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}

struct node {
char *id;
char *name;
char *regNo;
int msgCount;
struct node *next;
};

int main(int argc, char **argv){

int sockfd, newsockfd, portno, n;
char buffer[255];
struct sockaddr_in serv_addr, cli_addr;
socklen_t clilen;
pid_t pid;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0)
{
	error("Error opening socket");
}

bzero((char *)&serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(portno);

bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

listen(sockfd, 10);

while(1) {

clilen = sizeof(cli_addr);

newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

if(newsockfd < 0)
error("Error on Accept");

if((pid = fork()) == 0) {

close(sockfd);

bzero(buffer,sizeof(buffer));
read(newsockfd, buffer, 255);

struct node *head;
struct node *second;
struct node *third;
struct node *fourth;
struct node *fifth;
struct node *sixth;

head = (struct node *)malloc(sizeof(struct node));
second = (struct node *)malloc(sizeof(struct node));
third = (struct node *)malloc(sizeof(struct node));
fourth = (struct node *)malloc(sizeof(struct node));
fifth = (struct node *)malloc(sizeof(struct node));
sixth = (struct node *)malloc(sizeof(struct node));

head->id = "181527";
head->name = "Mukesh Kushwaha";
head->regNo = "2018-01-12-0039";
head->msgCount = 0;
head->next = second;

second->id = "181526";
second->name = "Min Raj Basnet";
second->regNo = "2018-01-12-0038";
second->msgCount = 0;
second->next = third;

third->id = "181531";
third->name = "Rajesh Singh";
third->regNo = "2018-01-12-0045";
third->msgCount = 0;
third->next = fourth;

fourth->id = "181529";
fourth->name = "Prakash Chand Kushwaha";
fourth->regNo = "2018-01-12-0041";
fourth->msgCount = 0;
fourth->next = fifth;

fifth->id = "181521";
fifth->name = "Samrat Chaudhary";
fifth->regNo = "2018-01-12-0028";
fifth->msgCount = 0;
fifth->next = sixth;

sixth->id = "181507";
sixth->name = "Asbin Khanal";
sixth->regNo = "2018-01-12-0015";
sixth->msgCount = 0;
sixth->next = NULL;


void displayInfo(struct node *ptr){
int flag = 0;
while(ptr != NULL){

if(strcmp(ptr->id, buffer) == 0){
char message[200] = "";
strcat(message,"Welcome ");
strcat(message,ptr->name);
strcat(message,", your unique identification key is : ");
strcat(message,ptr->regNo);
printf("\n%s\n", message);

n = write(newsockfd, message, strlen(message));
bzero(message, 200);

if(n < 0)
error("Error on writing on socket");

ptr->msgCount++;
printf("Request Count = %d\n", ptr->msgCount);
flag = 1;
break;
}
ptr = ptr->next;
}

if(flag != 1){
char temp[50] = "Invalid user";
write(newsockfd, temp, strlen(temp));
bzero(temp, 50);
printf("\nInvalid user: %s\n", buffer);
}
}

displayInfo(head);

char reply[10];
read(newsockfd, reply, 10);
printf("\n%s\n", reply);
bzero(reply, 10);

char replyMsg[100] = "\nDo you want to see your information again? (Type again)\n";

write(newsockfd, replyMsg, strlen(replyMsg));
bzero(replyMsg, 100);

while(1)
{
char temp[10];
read(newsockfd, temp, 10);
printf("\n%s", temp);

if(strcmp(temp, "again\n") == 0){
displayInfo(head);
printf("\nThank You\n");

bzero(temp, 10);
}

if(strcmp(temp, "quit\n") == 0){
printf("Exit from ID: %s\n", buffer);
break;
}
bzero(temp, 10);


}

close(newsockfd);
exit(0);
}
}
close(newsockfd);
return 0;

}
