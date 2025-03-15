#include <stdio.h>
#include <pthread.h>

#define COUNT 1000000
#define TH_N 5

pthread_mutex_t mut;

void *counter(void *x);

int main(){
   int i=0,c=0;
   pthread_t th[TH_N];
   pthread_mutex_init(&mut,NULL);

   for(i=0;i<TH_N;i++) pthread_create(&th[i],NULL,counter,&c);
   for(i=0;i<TH_N;i++) pthread_join(th[i],NULL);
   fprintf(stderr,"%d\n",c);
   return 0;
}
void *counter(void *x){
   int i;
   for(i=0;i<COUNT;i++) {
      pthread_mutex_lock(&mut);
      (*(int *)x)++;
      pthread_mutex_unlock(&mut);
   }
   return NULL;
}
/*

sasayama-no-MacBook-Air:Syoseki sasayama$ time ./thread_counter_mutex
5000000

real	0m50.078s
user	0m6.032s
sys	0m47.636s
*/

