//iterative chat server
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>


#define SERVER_IP "127.0.0.1"
// #define SERVER_PORT 5000

#define CLIENT_IP "127.0.0.1"
// #define CLIENT_PORT 5001

int main(int argc,char *argv[]){
	struct sockaddr_in server,client;
	char str[512],msg[512];
	int sd,slen=sizeof(server);
	
    printf("%d",argc);
    int SERVER_PORT=atoi(argv[1]);
    int CLIENT_PORT=atoi(argv[2]);

	bzero((char*)&client,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr(CLIENT_IP);
	client.sin_port=htons(CLIENT_PORT);

	bzero((char*)&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	server.sin_port=htons(SERVER_PORT);

	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&client,sizeof(client));
	
	connect(sd,(struct sockaddr*)&server,sizeof(server));
	do{
		printf("\nenter msg for server:");
		scanf("%s",str);
		send(sd,str,strlen(str)+1,0);
		if(strcmp(str,"stop")){
            memset(msg,0x0,512);
		    recv(sd,msg,512,0);
		    printf("server msg:%s",msg);
        }
		else break;
	}while(strcmp(msg,"stop"));
	close(sd);
	return 0;
}
