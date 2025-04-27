#include <stdio.h>
#include <stdlib.h>
#include <signal.h>  //usr/include/asm/signal.h
#include <time.h>
#include <unistd.h>

time_t start;
void stop(int x);

int main(){
   time(&start);
   signal(SIGINT,stop);
   while(1){
      sleep(1);
      fprintf(stderr, ".");
   }
   return 0;
}

void stop(int x){
   time_t end;
   time(&end);
   fprintf(stderr,"\n signal number=%d, time= %ld\n", x,end-start);
   exit(0);
}
