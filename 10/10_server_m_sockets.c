#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define BUF_SIZE 256
#define C_MAX 5

void stop(int x);
int sfd = -1;
int socketfds[C_MAX];

int main(int argc, char *argv[]){
   unsigned short port;
   int ret,ret_rcv,on=1,max=C_MAX,fd_max,i,n;
   fd_set rfds;
   struct sockaddr_in s_addr,c_addr;
   struct timeval tm;
   int addr_len=sizeof(struct sockaddr_in);
   char buf[BUF_SIZE];

   if(argc != 2){
      fprintf(stderr,"Usage: $ server <port>\n");
      exit(1);
   }
   port = (unsigned short)atoi(argv[1]);
   memset(&s_addr, 0, sizeof(s_addr));//受信バッファの初期化
   for(i=0;i<C_MAX;i++){//ソケットのファイルディスクプタの配列の初期化
      socketfds[i] = -1;
   }

   //シグナルハンドラの設定
   signal(SIGINT,stop);

   //ソケットの生成
   sfd=socket(PF_INET, SOCK_STREAM, 0);

   //TIME_WAIT中にサーバを再スタートしたとき、ポートを再利用できるようにする
   ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
   if(ret < 0){
      perror("setsockopt");
      exit(1);
   }

   //sockaddr_in構造体にIP,portをセット
   s_addr.sin_port = htons(port);
   s_addr.sin_family = PF_INET;
   s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   fprintf(stderr,"Address=%s, Port=%u\n",inet_ntoa(s_addr.sin_addr),port);
   
   //ソケットのbind
   ret = bind(sfd,(struct sockaddr *)&s_addr, sizeof(s_addr));
   if(ret < 0){
      perror("bind");
      exit(1);
   }
   //ソケットへの新規接続要求を受け付け開始
   ret = listen(sfd,5);
   if(ret < 0){
      perror("listen");
      exit(1);
   }
   fprintf(stderr,"Waiting for connection...\n");

   //selectループ(新規接続の有無または接続済みクライアントからのデータ受信のチェック)
   while(1){
      //fprintf(stderr,".");
      FD_ZERO(&rfds);//チェック用FD_ISSETで使うファイルディスクリプタ集合rfdsを初期化
      FD_SET(sfd,&rfds);//接続待ちのファイルディスクリプタをファイルディスクリプタ集合に設定
      fd_max = sfd;
      for(i=0;i<C_MAX;i++){
         if(socketfds[i] != -1){
            //受信待ちのファイルディスクリプタをファイルディスクリプタ集合に設定
            FD_SET(socketfds[i],&rfds);
            if(socketfds[i]>fd_max) fd_max = socketfds[i];
         }
      }
	  //selectで待機する時間の設定
	  tm.tv_sec = 5;
	  tm.tv_usec = 0;
      //接続や受信の監視
      ret = select(fd_max+1,&rfds,NULL,NULL,&tm);
      if(ret < 0){
         perror("select");
         break;
      }
      
     //接続待ちファイルディスクリプタに接続があったかどうか
      ret = FD_ISSET(sfd,&rfds);
      if(ret != 0){
         fprintf(stderr,"Accept new connection\n");
         for(i=0;i<C_MAX;i++){
            if(socketfds[i] == -1){//空いている配列にファイルディスクリプタ番号をいれる
			   //接続要求を受け付ける
               socketfds[i] = accept(sfd, (struct sockaddr *)&c_addr, (socklen_t *)&addr_len);
               fprintf(stderr,"client accepted(%d) from %s\n",i,inet_ntoa(c_addr.sin_addr));
               fprintf(stderr,"client fd number=%d\n",socketfds[i]);
               break;
            }
         }
      }
	  //接続中のすべてのクライアントとの送受信
      for(i=0;i<C_MAX;i++){
         if(socketfds[i] != -1){//acceptしたファイルディスクリプタのみチェック
            ret = FD_ISSET(socketfds[i],&rfds);//ファイルディスクリプタにデータがあるかどうか
            if(ret != 0){
               memset(buf,0,BUF_SIZE);
               ret_rcv = recv(socketfds[i], buf, BUF_SIZE, 0);
               if(ret_rcv > 0){//受信成功
                  fprintf(stderr,"received: %s\n", buf);
                  n = strlen(buf);
                  send(socketfds[i],&n,ret_rcv,0);
                  if(strcmp(buf,"exit") == 0){
                     close(socketfds[i]);
                     socketfds[i] = -1;
                  }
               }
               else{
                  fprintf(stderr,"socket=%d disconnected: \n", socketfds[i]);
                  close(socketfds[i]);
                  socketfds[i] = -1;
               }
            }
         }
      }
   }//selectループの最後

   //ソケットのクローズ
   close(sfd);
}

void stop(int x){
   int i;
   if( sfd != -1){
      close(sfd);
   }
   for(i=0;i<C_MAX;i++){
      if(socketfds[i] != -1){   
	     close(socketfds[i]);
      }
   }
   exit(1);
}
