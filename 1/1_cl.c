#include <stdio.h>

int main(int argc, char *argv[]){
    fprintf(stderr, "argc=%d\n", argc);
    fprintf(stderr, "argv[0]=%s\n", argv[0]);
fprintf(stderr, "argv[1]=%s\n", argv[1]);
fprintf(stderr, "argv[2]=%s\n", argv[2]);
    return 0;
}
