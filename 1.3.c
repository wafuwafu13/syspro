#include <stdio.h>
void sum(int *n, int *m) {
    *n = *n + 1;
    *m = *m + 1;
}

int main() {
    int a = 1, b= 2;
    sum(&a, &b);
    printf("a=%d\nb=%d\n", a, b);
    return 0;
}