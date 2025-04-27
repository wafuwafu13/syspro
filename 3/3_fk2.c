#include <stdio.h>
#include <unistd.h>
#define N 10
int main(void){
   pid_t pid;
   int i;
   pid = fork();//子プロセスの生成
   if(pid==0){
      for(i=0;i<N;i++){
         fprintf(stderr, "子プロセス i=%d\n", i);
      }
   }
   else{
      for(i=0;i<N;i++){
         fprintf(stderr, "親プロセス i=%d\n", i);
      }
   }
   return 0;
}
