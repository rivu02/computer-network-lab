//iterative chat server
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define SERVER_IP "127.0.0.1"
// #define SERVER_PORT 5000

int main(int argc,char *argv[]){
	struct sockaddr_in server,client;
	char buff1[512],buff2[512],*msg;
	int sd,nsd,clen=sizeof(client);
	
    int SERVER_PORT=atoi(argv[1]);
	bzero((char*)&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	server.sin_port=htons(SERVER_PORT);
	
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&server,sizeof(server));
	
	listen(sd,5);
	while(1){
		nsd=accept(sd,(struct sockaddr*)&client,&clen);
		do{
			memset(buff1,0x0,512);
			recv(nsd,buff1,512,0);
			printf("\nclient msg: %s",buff1);
            // puts(buff1);
            if(strcmp(buff1,"stop")){
                  printf("\nenter msg for client:");
                scanf("%s",buff2);
			    send(nsd,buff2,strlen(buff2)+1,0);
            }
		}while(strcmp(buff1,"stop"));
		close(nsd);
	}	
	return 0;
}
