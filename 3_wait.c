#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(void){
   pid_t pid;
   int st;
   pid = fork();
   if(pid==0){
       fprintf(stderr, "child pid=%d\n", getpid() );
       exit(0);
   }
   else{
       fprintf(stderr, "parent pid=%d\n", getpid() );
       pid=wait(&st);
       fprintf(stderr, "pid= %d st=%d\n",pid,st);
   }
   return 0;
}
