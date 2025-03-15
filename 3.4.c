#include <stdio.h>
#include <unistd.h>

int main(void){
   pid_t pid, pid2;
   int i;
   pid = fork();
   if (pid == 0){
        printf("子プロセス 1 \n");
   } else {
    pid2 = fork();
    if (pid2 == 0){
        printf("子プロセス 2 \n");
    }
   }
   return 0;
}