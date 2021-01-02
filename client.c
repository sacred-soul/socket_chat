#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#define SER_PORT 1200
int main()
{
    int exit_flag=0,client_sock;
    char str[50],str2[50],local_host[]="127.0.0.1";
    struct sockaddr_in client_addr;
    client_addr.sin_port=htons(SER_PORT);
    client_addr.sin_family=AF_INET;
    client_addr.sin_addr.s_addr=inet_addr(local_host);
    client_sock=socket(AF_INET,SOCK_STREAM,0);
    if(client_sock<0)
    {
        perror("Invalid address : Address not supported \n");
        exit(0);
    }
    if(connect(client_sock,(struct sockaddr*)&client_addr,sizeof(client_addr))<0)
    {
        perror("Connection Failed \n");
        exit(0);
    }
    printf("Client connected to %s \n",local_host);
    printf("\nClient msg : ");
    gets(str);
    if(write(client_sock,str,sizeof(str))<0)
        printf("Data could not be sent\n");

    while(exit_flag <= 1)
    {   
        listen(client_sock,1);
        read(client_sock,str2,sizeof(str2));
        printf("Server msg : %s\n",str2);
        if(strcmp(str2,"BYE") == 0)
            exit_flag++;
        if (exit_flag <=1)
        {
            printf("Client msg : ");
            gets(str);
            write(client_sock,str,sizeof(str));
            if(strcmp(str,"BYE") == 0)
                exit_flag++;
        }
    }
    close(client_sock);
    return 0;
}