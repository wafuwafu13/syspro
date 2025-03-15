#include <stdio.h>
#include <unistd.h>
int main(void){
   fprintf(stderr,"execl実行前\n");
   getchar();
   execl("/bin/less", "less", "exeA.c", NULL);
   return 0;
}
