#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void func(int x);

int main(){
   int num1,num2,ans,in_ans;
   signal(SIGALRM,func);

   srand(time(NULL));
   num1 = rand() % 100;
   num2 = rand() % 100;
   ans = num1 + num2;
   fprintf(stderr, "%d + %d ? ", num1,num2);

   alarm(5);
   scanf("%d",&in_ans);
   alarm(0);
   
   if( ans == in_ans ){
      fprintf(stderr, "You got it.\n");
   }
   else{
      fprintf(stderr, "That's wrong.\n");
   }
   return 0;
}
void func(int x){
   fprintf(stderr, "Time is up!\n");
}
