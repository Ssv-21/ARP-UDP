#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<stdlib.h>
#define MAX 1000
int main(int argc,char *argv[])
{
    int serverDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    printf("--->Client Socket Created<---\n");
    char buffer[MAX], message[MAX];
    struct sockaddr_in cliaddr, serverAddress;
    socklen_t serverLength = sizeof(serverAddress);

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(atoi(argv[2]));

    bind(serverDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    while (1)
    {
        printf("Enter the command for execution:- ");
        fgets(buffer, sizeof(buffer), stdin);
        sendto(serverDescriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, serverLength);
         recvfrom(serverDescriptor, message, sizeof(message), 0, (struct sockaddr *)&serverAddress, &serverLength);
        printf("execution Reslut from Server is:  %s",message);
    }
    return 0;
}
