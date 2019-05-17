#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 256






void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}

void commun(int sock){
	char buf[BUF_SIZE];
	int len_r;
	if((len_r=recv(sock,buf,BUF_SIZE,0))<=0)DieWithError("recv()faile");
	buf[len_r]='\0';
	printf("%s\n",buf);
	if(send(sock,buf,strlen(buf),0)!=strlen(buf))DieWithError("tanaka()faile");
	
}





int main (int argc ,char **argv){
	
	int servSock = socket(PF_INET,SOCK_STREAM,0);	
	int cliSock;
	struct sockaddr_in servAddess;
	struct sockaddr_in clientAddess;
	unsigned int szClientaddr;
	
	servAddess.sin_family = AF_INET;
	servAddess.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddess.sin_port=htons(10001);
	bind(servSock,(struct sockaddr *)&servAddess,sizeof(servAddess));
	
	listen(servSock,5); //順番待ちマテル数５//
	while(1){
		szClientaddr = sizeof(clientAddess);
		cliSock=accept(servSock,(struct sockaddr *)&clientAddess,&szClientaddr);
		commun(cliSock);
	}
	close(servSock);
	return 0;
}


