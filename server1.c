#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main() {
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
perror("Error opening socket");
exit(1);
}
bzero((char *) &serv_addr, sizeof(serv_addr));
portno = 12345;
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
perror("Error on binding");
exit(1);
}
listen(sockfd, 5);
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
if (newsockfd < 0) {
perror("Error on accept");
exit(1);
}
bzero(buffer, 256);
int n = read(newsockfd, buffer, 255);
if (n < 0) {
perror("Error reading from socket");
exit(1);
}
printf("Message from client: %s\n", buffer);
n = write(newsockfd, buffer, strlen(buffer));
if (n < 0) {
perror("Error writing to socket");
exit(1);
}
close(newsockfd);
close(sockfd);
return 0;
}
