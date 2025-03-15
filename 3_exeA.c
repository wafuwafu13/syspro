#include <stdio.h>
#include <unistd.h>
int main(void){
   fprintf(stderr,"execl実行前\n");
   execl("/bin/ls", "/bin/ls", "-l", NULL);
   fprintf(stderr,"execl実行後\n");
   return 0;
}
