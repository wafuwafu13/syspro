#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]){
   unsigned short port;
   int sfd=-1, cfd=-1;//サーバ用ソケットとクライアント用ソケット
   int ret, n, on=1;
   struct sockaddr_in s_addr, c_addr;
   int addr_len=sizeof(struct sockaddr_in);
   char buf[BUF_SIZE];

   if(argc!=2){
      fprintf(stderr,"Usage: $ ./server_socket [port]\n");
      exit(1);
   }
   port=(unsigned short)atoi(argv[1]);

   //ソケットの生成
   sfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   //TIME_WAIT中にサーバを再スタートしたとき、ポートを再利用できるようにする
   ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
   if(ret < 0){
      perror("setsockopt");
      exit(1);
   }
   //sockaddr_in構造体にIP,portをセット
   memset(&s_addr, 0, sizeof(s_addr));//受信バッファの初期化
   s_addr.sin_port = htons(port);
   s_addr.sin_family = AF_INET;
   s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   fprintf(stderr,"Address=%s, Port=%u\n",inet_ntoa(s_addr.sin_addr),port);

   //ソケットのbind
   bind(sfd,(struct sockaddr *)&s_addr, sizeof(s_addr));

   //接続を待つ
   listen(sfd,5);
   fprintf(stderr,"Waiting for connection...\n");

   //接続要求を受け付ける
   cfd = accept(sfd, (struct sockaddr *)&c_addr, &addr_len);
   fprintf(stderr,"Connected from %s\n", inet_ntoa(c_addr.sin_addr));

   //クライアントとの送受信ループ
   while(1){
      memset(buf,0,BUF_SIZE);
      ret = recv(cfd, buf, BUF_SIZE, 0);
      if(ret == 0 || ret == -1){
         break;
      }
      fprintf(stderr, "received: %s\n",buf);
      n=strlen(buf);
      send(cfd, &n, ret, 0);
	  ret = strcmp(buf,"exit");
      if(ret == 0 )break;
   }

   //ソケットのクローズ
   if( sfd != -1){
      close(sfd);
   }
   if( cfd != -1){
      close(cfd);
   }
   return 0;
}
