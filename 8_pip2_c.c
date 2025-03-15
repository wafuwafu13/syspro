#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
   char word[256];
   int n, rfd, wfd;

   rfd=atoi(argv[1]);
   wfd=atoi(argv[2]);
   read(rfd, word, sizeof(word));
   fprintf(stderr,"x\n");
   
   n=strlen(word);

   write(wfd, &n, sizeof(n));

   close(rfd);
   close(wfd);
   fprintf(stderr,"y\n");
   return 0;
}

