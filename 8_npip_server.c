#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
int main(){//server
   int fd,n;
   char *myfifo = "./named_pipe";
   char line[256],word[256];

   mkfifo(myfifo,0666);
   while(1){
      fd = open(myfifo, O_RDONLY);
      read(fd, word, sizeof(word));
      fprintf(stderr, "crient: %s \n", word);
      close(fd);

      fd = open(myfifo, O_WRONLY);
      n = strlen(word);
      write(fd, &n, sizeof(n));
      close(fd);
   }
   return 0;
}
