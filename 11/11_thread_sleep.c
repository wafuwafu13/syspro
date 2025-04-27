#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *processing(void *x);
int main(){
   pthread_t th;
   int i,flag = 0;

   pthread_create(&th, NULL, processing, &flag);
   fprintf(stderr,"processing");
   i = 1;
   while(1){
      if(flag == 1)break;
      if(i%4 == 0) fprintf(stderr,"\rprocessing    \rprocessing");
      else fprintf(stderr,".");
      sleep(1);
      i++;
   }
   pthread_join(th,NULL);
   return 0;
}

void *processing(void *x){

   sleep(20);//重い処理に見立てる

   *(int *)x = 1;
   fprintf(stderr,"\ndone.\n"); 
   return NULL;
}
