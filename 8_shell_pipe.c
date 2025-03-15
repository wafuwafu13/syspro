#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int get_arg2(char *c, char *arg[],char *sym);
 
int main(){
   pid_t pid;
   char line[256],command[256],*divcom[32],*arg_c1[32],*arg_c2[32];
   int st,i=0,ret1,ret2,ret3,ret4,fd[2];

   while(1){
      fprintf(stderr,"--> ");
      fgets(line,sizeof(line),stdin);
      ret1 = sscanf(line,"%[^\n]",command);
      if(ret1 > 0){
         ret2 = get_arg2(command,divcom,"|");
         if(ret2 == 1){
            get_arg2(divcom[0], arg_c1," ");
            pid = fork();
            if(pid == 0){
               ret3 = execv(arg_c1[0],arg_c1);
               if(ret3 < 0){
                  exit(0);
		       }
            }
            else{
               wait(&st);
            }
         }
         else if(ret2 == 2){
            get_arg2(divcom[0], arg_c1," ");
            get_arg2(divcom[1], arg_c2," ");

            ret3 = pipe(fd);
            if(ret3 < 0){
               perror("pipe");
               exit(1);
            }
            pid = fork();
            if(pid == 0){
               close(fd[0]);
               dup2(fd[1],STDOUT_FILENO);
               ret4 = execv(arg_c1[0],arg_c1);
               if(ret4 < 0){
                  exit(0);
               }
            }
            pid = fork();
            if(pid == 0){
               close(fd[1]);
               dup2(fd[0],STDIN_FILENO);
               ret4 = execv(arg_c2[0],arg_c2);
               if(ret4 < 0){
                  exit(0);
               }
            }
            close(fd[0]);
            close(fd[1]);//2つめのwaitより前に実行しないと２つめのプロセスが終了しない
            wait(&st);
            wait(&st);
         }
      }
   }
   return 0;
}

int get_arg2(char *c, char *arg[], char *sym){
    int i = 0;
    arg[i] = strtok(c,sym);
    while(arg[i] != NULL){
        i++;
        arg[i] = strtok(NULL,sym);
    }
    return i;
}
