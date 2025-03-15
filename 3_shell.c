#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(void){
    pid_t pid;
    int st,ret;
    char line[256],command[256];
    while(1){
        fprintf(stderr, "--> ");
        fgets(line,sizeof(line), stdin);
        sscanf(line,"%s",command);
        pid = fork();
        if(pid == 0){
            ret=execl(command,command,NULL);
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
