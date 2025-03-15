#include <stdio.h>

int main(int argc, char *argv[]){
   if(argc != 3){
       fprintf(stderr, "Usage:cl_err f1 f2\n");
       return 1;
   }
   fprintf(stderr, "OK\n");
   return 0;
}
