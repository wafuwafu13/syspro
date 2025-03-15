#include <stdio.h>

struct denwacho{
   char name[40];
    char tel[12];
    int age;
};

int main(){
    struct denwacho friend;
    scanf("%s", friend.name);
    scanf("%s", friend.tel);
    scanf("%d", &friend.age);
    fprintf(stderr, "friend.name=%s\n", friend.name);
    fprintf(stderr, "friend.tel=%s\n", friend.tel);
    fprintf(stderr, "friend.age=%d\n", friend.age);
    return 0;
}
