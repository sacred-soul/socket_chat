#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define SER_PORT 1200
int main()
{
    int exit_flag=0;
    int server_sock,newsock;
    char str[50],str2[50];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_info;
    socklen_t csize=sizeof(client_info);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(SER_PORT);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    if((server_sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Socket failed !\n");
        exit(0);
    }
    if(bind(server_sock,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
    {
        printf("Binding failed\n");
        exit(0);
    }
    if(listen(server_sock,1)<0)
        printf("Listen failed\n");
    if((newsock=accept(server_sock,(struct sockaddr *)&client_info,&csize))<0)
    {
        printf("Accept failed\n");
        exit(0);
    }
    else
        printf("Connected to %s\n\n",inet_ntoa(client_info.sin_addr));
    read(newsock,str,sizeof(str));
    printf("Client msg : %s\n",str);
    while(exit_flag <= 1)
    {   
        printf("Server msg : ");
        gets(str2);
        write(newsock,str2,sizeof(str2));
        if(strcmp(str2,"BYE") == 0)
            exit_flag++;
        if(exit_flag <=1 )
        {
        listen(newsock,1);
        read(newsock,str,sizeof(str));
        if(strcmp(str,"BYE") == 0)
            exit_flag++;
        printf("Client msg : %s\n",str);
        }
    }
    close(newsock);
    close(server_sock);
    return 0;
}