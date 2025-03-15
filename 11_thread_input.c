#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define DATA_N 100000
#define LOOP_N DATA_N/10

long count;
void *input(void *x);
void *query(void *x);
int main(int argc, char *argv[]){
  int i,j;
  double data[DATA_N];
  pthread_t th1,th2;

  count = 0;
  pthread_create(&th1,NULL,input,data);
  pthread_create(&th2,NULL,query,NULL);

  pthread_join(th1,NULL);
  return 0;
}
void *input(void *x){
  int i,j;
  fprintf(stderr,"Calculating...");
  for(i=0;i<LOOP_N;i++){
     for(j=0;j<DATA_N;j++){
        ((int *)x)[j] = 0.0;
        count++;
     }
  }
  fprintf(stderr,"\ndone.\n");
  return NULL;
}

void *query(void *x){
  while(1){
     getchar();
     fprintf(stderr,"count=%ld",count);
  }
  return NULL;
}
