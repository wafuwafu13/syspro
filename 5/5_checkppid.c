#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;

    pid=fork();
    if(pid==0){
        sleep(20);
	    fprintf(stderr,"子プロセス終了\n");
        exit(0);
    }
    else{
        getchar();
        fprintf(stderr,"親プロセス終了\n");
    }
    return 0;
}
