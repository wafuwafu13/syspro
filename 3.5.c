#include <stdio.h>
#include <unistd.h>
int main(void){
   execl("/usr/bin/gcc", "gcc", "-o", "file", "3q-4.c", NULL);
   return 0;
}