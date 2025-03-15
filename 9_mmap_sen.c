#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(){
   char *p,line[4096],command[4096];
   int fd,ret1;

   fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
   if(fd == -1){ 
      fprintf(stderr, "shm_open failed\n");
      exit(1);
   }

   ret1 = ftruncate(fd ,sizeof(line));
   if(ret1 < 0){
      perror("ftruncate");
      exit(1);
   }

   p = mmap(NULL, sizeof(line), PROT_WRITE, MAP_SHARED, fd, 0);
   if(p == MAP_FAILED){ 
      perror("mmap"); 
      exit(1);
   }

   fgets(line, sizeof(line), stdin);
   ret1 = sscanf(line,"%[^\n]",command);
   if(ret1 > 0){
      strncpy(p, command, sizeof(command));
   }
   if(munmap(p, sizeof(line)) == -1){ 
      perror("munmap"); 
      return 1;
   }
   close(fd);
   return 0;
}
