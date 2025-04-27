#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
int main(){
   int fd,ret1,n;
   char *myfifo = "./named_pipe";
   char line[256], word[256];

   mkfifo(myfifo,0666);
   while(1){
      fgets(line, sizeof(line), stdin);
      ret1 = sscanf(line, "%[^\n]", word);
      if( ret1 > 0 ){
         fd = open(myfifo, O_WRONLY);
         write(fd, word, sizeof(word));
         close(fd);

         fd = open(myfifo, O_RDONLY);
         read(fd, &n, sizeof(n));
         fprintf(stderr, "%s <-> %d \n", word, n);
         close(fd);
      }
   }
   return 0;
}
