#include <stdio.h>
// アドレスの中身を受け取る
void kan(int *p) {
    scanf("%d", p);
}

int main(void) {
    int n;
    // アドレスを渡す
    kan(&n);
    printf("n=%d\n", n);
    return 0;
}