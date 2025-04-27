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
   char *server_ip;
   unsigned short port;
   int myfd=-1,ret,ret_rcv,n;
   struct sockaddr_in my_addr;
   char word[BUF_SIZE];

   if(argc != 3){
      fprintf(stderr,"Usage:$ ./client_socket [ip_address] [port]\n");
      exit(1);
   }
   server_ip = argv[1];
   port = (unsigned short)atoi(argv[2]);
   myfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   memset(&my_addr, 0, sizeof(my_addr));
   my_addr.sin_port = htons(port);
   my_addr.sin_family = AF_INET;
   my_addr.sin_addr.s_addr = inet_addr(server_ip);

   fprintf(stderr,"Connecting to %s:\n", server_ip);
   //サーバのソケットに接続する
   connect(myfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

   //サーバとの送受信ループ
   while(1){
      memset(word,0,BUF_SIZE);
      fprintf(stderr,"> ");
      fgets(word,sizeof(word),stdin);
      word[strlen(word)-1] = '\0';
      send(myfd,word, strlen(word),0);
      ret = strcmp(word,"exit");
      if(ret == 0) break;

      ret = recv(myfd, &n, BUF_SIZE,0);
      if(ret == 0 || ret == -1){
         break;
      }
      fprintf(stderr,"from server: %d\n",n);
   }
   //ソケットのクローズ
   if(myfd != -1){
      close(myfd);
   }
   return 0;
}
