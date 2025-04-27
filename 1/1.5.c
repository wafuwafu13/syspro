#include <stdio.h>

struct kozo{
    char name[40];
    int age;
};

int main(){
    struct kozo data[20];
    data->age = 21;
    return 0;
}