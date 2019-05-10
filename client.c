#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h> //clooseを使うため//
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define BUF_SIZE 256

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}



void commun(int sock){
	char buf[BUF_SIZE];
	int len_r;
	char *message="世界的な人気を誇る「ポケットモンスター」をシリーズで初めて実写化した「名探偵ピカチュウ」が、5月3日に日本先行公開";
	if(send(sock,message,strlen(message),0)!=strlen(message)){
		DieWithError("send() sent a message of unexpected bytes");}
	if((len_r=recv(sock,buf,256,0))<=0)DieWithError("recv()faile");
	buf[len_r]='\0';
	printf("%s\n",buf);
}


int main(int argc,char **argv){
	
	
	if (argc != 3)
		DieWithError("arguments is not available");
	char *server_ipaddr=argv[1];  //"10.13.64.20"//
	int server_port=atoi(argv[2]);  //10001//
	
	int sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock<0)DieWithError("socket()failed"); //socket=-1はエラー//
	struct sockaddr_in target;
	target.sin_family=AF_INET;
	target.sin_addr.s_addr=inet_addr(server_ipaddr);
	target.sin_port=htons(server_port);
	if(connect(sock,(struct sockaddr*)&target, sizeof(target))<0)
		DieWithError("connect() failed");
	
	//printf("SOCK IS %d\n",sock);

	commun(sock); //長くなったのでメッセージのやり取りは関数にスる//
	close(sock);
	return 0;
}
