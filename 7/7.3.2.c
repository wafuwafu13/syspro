#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(void){
   pid_t pid;
   int st;
   pid = fork();
   fprintf(stderr, "pid=%d\n", getpid() ); // 5566 5567
   if(pid==0){
       fprintf(stderr, "child pid=%d\n", getpid() ); // 5567
       sleep(5);
       exit(0);
   }
   else{
       fprintf(stderr, "parent pid=%d\n", getpid() ); // 5566
       pid=wait(&st); // 5秒待ってる
       fprintf(stderr, "pid= %d st=%d\n",pid,st); // 5567, 0
   }
   return 0;
}