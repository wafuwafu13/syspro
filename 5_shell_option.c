#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int get_arg(char *c, char *arg[]);
int main(){
   pid_t pid;
   int ret,st,i=0;
   char line[256],command[256],*arg[32];
   while(1){
      fprintf(stderr,"--> ");
	  fgets(line,sizeof(line),stdin);
	  sscanf(line,"%[^\n]",command);

      get_arg(command, arg);

      pid = fork();
	  if(pid == 0){
	     ret = execv(arg[0],arg);
	     if(ret < 0){
		    exit(0);
		 }
	  }
	  else{
	     wait(&st);
	  }
   }
   return 0;
}
int get_arg(char *c, char *arg[]){
   int i=0;
   arg[i] = strtok(c," ");
   while(arg[i] != NULL){
      i++;
	  arg[i] = strtok(NULL," ");
   }
   return i;
}
