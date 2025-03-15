#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
    pid_t pid;
    int st;
    pid=fork();
    if(pid==0){
        exit(0);
    }
    else{
        sleep(20);
        wait(&st);
        fprintf(stderr,"正常終了\n");
    }
    return 0;
}
