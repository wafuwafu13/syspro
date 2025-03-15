#include <stdio.h>
#include <unistd.h>
int main(void){
   pid_t pid;
   pid_t fpid;
   fpid = fork();
   fprintf(stderr, "fpid=%d\n", fpid); // 5158, 0
   pid = getpid();
   fprintf(stderr, "pid=%d\n", pid); // 5157, 5158
   if(fpid==0){
        pid = getpid();
        fprintf(stderr, "子プロセス pid=%d\n", pid); // 5158
   }
   else{
        pid = getpid();
        fprintf(stderr, "親プロセス pid=%d\n", pid); // 5157
   }
   return 0;
}