#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000

int main(){
	struct sockaddr_in server,client;
	char buff1[512],buff2[]="Invlid msg",*msg;
	int sd,nsd,clen=sizeof(client);
	time_t ti;
	bzero((char*)&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	server.sin_port=htons(SERVER_PORT);
	
	sd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sd,(struct sockaddr*)&server,sizeof(server));
	
	
	while(1){
	
		do{
			memset(buff1,0x0,512);
			recvfrom(sd,buff1,512,0,(struct sockaddr*)&client,&clen);
			if(!strcmp(buff1,"time")){
				ti=time(NULL);
				msg=ctime(&ti);
				sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&client,sizeof(client));
			}
			else
				sendto(sd,buff2,strlen(buff2)+1,0,(struct sockaddr*)&client,sizeof(client));
		}while(strcmp(buff1,"stop"));
		close(sd);
	}	
	return 0;
}
