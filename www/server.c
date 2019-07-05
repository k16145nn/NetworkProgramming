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
	char buf2[2*BUF_SIZE];
	char buf_old[BUF_SIZE];
	int len_r;
	char response[BUF_SIZE];
	
	while((len_r=recv(sock,buf,BUF_SIZE,0))>0){
		buf[len_r]='\0';
		sprintf(buf2,"%s%s",buf_old,buf);
		printf("%s\n",buf);
		if(strstr(buf2,"\r\n\r\n")){
			break;
		}
	}
	if(len_r <=0)
		DieWithError("recv()faile");
	printf("received HTTP Request,\n");
	
	sprintf(response, "HTTP/1.1 200 OK\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "Content-Type: text/html; charset=utf-8\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
        
    sprintf(response, "\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "<!DOCTYPE html><html><head><title>");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "ネットワークプログラミングのwebサイト");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "</title></head><body>ネットワークダイスキ</body></html>");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
}





int main (int argc ,char **argv){
	
	int servSock = socket(PF_INET,SOCK_STREAM,0);	
	int cliSock;
	struct sockaddr_in servAddess;
	struct sockaddr_in clientAddess;
	unsigned int szClientaddr;
	
	servAddess.sin_family = AF_INET;
	servAddess.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddess.sin_port=htons(80);
	bind(servSock,(struct sockaddr *)&servAddess,sizeof(servAddess));
	
	listen(servSock,5); //順番待ちマテル数５//
	while(1){
		szClientaddr = sizeof(clientAddess);
		cliSock=accept(servSock,(struct sockaddr *)&clientAddess,&szClientaddr);
		commun(cliSock);
		close(cliSock);
	}
	close(servSock);
	return 0;
}

