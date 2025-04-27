#include <stdio.h>
#include <pthread.h>

#define COUNT 1000000
#define TH_N 5

void *counter(void *x);

int main(){
   int i=0,c=0;
   pthread_t th[TH_N];

   for(i=0;i<TH_N;i++) pthread_create(&th[i],NULL,counter,&c);
   for(i=0;i<TH_N;i++) pthread_join(th[i],NULL);
   fprintf(stderr,"%d\n",c);
   return 0;
}
void *counter(void *x){
   int i;
   for(i=0;i<COUNT;i++) {
      (*(int *)x)++;
   }
   return NULL;
}
/*
sasayama-no-MacBook-Air:Syoseki sasayama$ time ./thread_counter
3408161

real	0m0.036s
user	0m0.043s
sys	0m0.005s
*/
