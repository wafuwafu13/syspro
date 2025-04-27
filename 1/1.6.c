#include <stdio.h>

int main(){
    struct denwa{
        char name[50];
        int age;
    };    
    struct denwa data[3];
    struct denwa *p;
	  int i;
    p=data;
    for(i=0;i<3;i++){
      scanf("%s%d", p->name, &p->age);
      p++;
    }
    p=data;
    for(i=0;i<3;i++){
      printf("%s %d\n", p->name, p->age);
      p++;
    }
    return 0;
}
