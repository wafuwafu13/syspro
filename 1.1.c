#include <stdio.h>
int main() {
    int a=1, b=2, *x, *y, ans1, ans2, ans3;
    x = &a;
    y = &b;
    ans1 = a + b;
    ans2 = a + *y;
    ans3 = *x + *y;
    printf("ans1=%d\nans2=%d\nans3=%d\n", ans1, ans2, ans3);
    return 0;
}