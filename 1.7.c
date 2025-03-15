#include <stdio.h>

struct denwacho{
    char name[40];
    char tel[12];
    int age;
};

int main(){
    struct denwacho friend[3];
	int i;
    for(i=0;i<3;i++){
      scanf("%s", friend[i].name);
      scanf("%s", friend[i].tel);
      scanf("%d", &friend[i].age);
    }
    for(i=0;i<3;i++){
      fprintf(stderr, "friend[%d].name=%s\n", i, friend[i].name);
      fprintf(stderr, "friend[%d].tel=%s\n", i, friend[i].tel);
      fprintf(stderr, "friend[%d].age=%d\n", i, friend[i].age);
    }
    return 0;
}