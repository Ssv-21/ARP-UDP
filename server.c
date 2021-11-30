#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 10000  
int main(int argc,char *argv[])
{ 
    FILE *fp1,*fp2;
   char buff[1000];int i,j;char message[1000];
    int serverDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    printf("--->Server Socket Created<---\n");
    int size;
    char buffer[MAX];
    struct sockaddr_in clientAddress, serverAddress;

    socklen_t clientLength = sizeof(clientAddress);

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr =inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(atoi(argv[1]));
  
    bind(serverDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    printf("...Binded Sucessfully...\n");
    while (1)
    {
        fp1=fopen("store.txt","w");
        bzero(buffer, sizeof(buffer));
        recvfrom(serverDescriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, &clientLength);
        printf("Command requested by the client is:- %s",buffer);
        char file[100]=">>store.txt";
        for(i=0;buffer[i+1]!=0;i++);
        for(j=0;file[j]!=0;j++,i++)
           buffer[i]=file[j];
        system(buffer);
        fp2=fopen("store.txt","r");
        bzero(message, sizeof(message));
        fread(&message,sizeof(char),1000,fp2);
        printf("--->Command executed sucessfully and Result sent to client<---\n");
        sendto(serverDescriptor, &message, sizeof(message), 0, (struct sockaddr *)&clientAddress, clientLength);
    }
    close(serverDescriptor);
    return 0;
}
