#include <stdio.h>
void func(int n, int d[5]) {
    int i;
    for(i=0; i<n; i++) {
        d[i] = d[i] * 10;
    }
}
int main() {
    int i, k=5;
    int arr[5] = {1,2,3,4,5};
    printf("arr[3]=%d\n", arr[3]);
    func(k, arr);
    printf("arr[3]=%d\n", arr[3]);
    return 0;
}