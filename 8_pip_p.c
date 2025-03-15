#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
   pid_t pid;
   char line[256], rfd[5], wfd[5], word[256];
   int n, fd[2], st, ret1, ret2;

   ret1 = pipe(fd);
   if(ret1 < 0){
      perror("pipe");
      exit(1);
   }

   snprintf(rfd, sizeof(rfd), "%d", fd[0]);
   snprintf(wfd, sizeof(wfd), "%d", fd[1]);

   fgets(line, sizeof(line), stdin);
   ret1 = sscanf(line, "%s", word);
   if(ret1 > 0){
      pid = fork();
      if(pid==0){
         ret2 = execl("pip_c","pip_c", rfd, wfd, NULL);
         if(ret2 < 0){
            exit(1);
         }
      }
      write(fd[1], word, sizeof(word));
      wait(&st);

      read(fd[0], &n, sizeof(n));
      fprintf(stderr, "%s <-> %d \n", word, n);

      close(fd[0]);
      close(fd[1]);
   }
   return 0;
}
/*
apple
apple <-> 5 
 */

