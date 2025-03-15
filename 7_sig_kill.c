#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
   int ret;
   pid_t pid;
   if(argc != 2){
      fprintf(stderr, "Only one PID is required\n");
      exit(1);
   }
   pid=atoi(argv[1]);
    
   ret = kill(pid, SIGKILL);
   if(ret<0){ 
       perror("kill");
   }
   return 0;
}
