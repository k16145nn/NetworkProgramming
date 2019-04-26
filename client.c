#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h> //clooseを使うため//
#include<string.h>
#include<unistd.h>
void commun(int sock){
	char buf[256];
	int len_r;
	char *message="世界的な人気を誇る「ポケットモンスター」をシリーズで初めて実写化した「名探偵ピカチュウ」が、5月3日に日本先行公開";
	send(sock,message,strlen(message),0);
	len_r=recv(sock,buf,256,0);
	buf[len_r]='\0';
	printf("%s\n",buf);
}


int main(int argc,char **argv){
	int sock=socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in target;
	target.sin_family=AF_INET;
	target.sin_addr.s_addr=inet_addr("10.13.64.20");
	target.sin_port=htons(10001);
	connect(sock,(struct sockaddr*)&target, sizeof(target));
	//printf("SOCK IS %d\n",sock);

	commun(sock); //長くなったのでメッセージのやり取りは関数にスる//
	close(sock);
	return 0;
}
