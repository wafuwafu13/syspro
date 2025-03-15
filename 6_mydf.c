#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/vfs.h>

int main(int argc, char *argv[]){
   struct statfs buf;
   double gb=1024.0*1024.0*1024.0;
   int ubs,ret;

   sync();
   ret=statfs(argv[1],&buf);
   if(ret<0){
	  exit(0);
   }
   fprintf(stderr,"%.1f GB\n", buf.f_blocks*buf.f_bsize/gb);
   
   ubs = buf.f_blocks-buf.f_bfree;
   fprintf(stderr,"usedsize=%.0f GB\n", ubs*buf.f_bsize/gb);
   fprintf(stderr,"freesize=%.0f GB\n",buf.f_bfree*buf.f_bsize/gb);
   fprintf(stderr,"used rasio=%.0f %%\n", 100.0*ubs/buf.f_blocks);
   return 0;
}
