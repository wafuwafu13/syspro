#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
   char *p;
   int fd,ret;

   fd = shm_open("/shared_memory", O_RDONLY, 0666);
   if(fd == -1){  
      fprintf(stderr, "shm_open failed\n");
      exit(1);
   }
   p = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);
   if(p == MAP_FAILED){ 
      perror("mmap"); 
      exit(1);
   }

   fprintf(stderr,"%s\n",p);

   ret = munmap(p, sizeof(char));
   if(ret == -1){
      perror("munmap"); 
      exit(1);
   }
   shm_unlink("/shared_memory");
   close(fd);
   return 0;
}
