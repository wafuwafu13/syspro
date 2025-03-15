#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/sem.h>
//shared memoryの文字列受け取って文字数を代入する側
int main(int argc, char *argv[]){
   char *p,*ptr,count[4096];
   int fd,ret1,semid,n,i;
   key_t semkey;
   struct sembuf buf;

   semkey = ftok("mmap2_r_sem",'a');
   semid = semget(semkey,1,IPC_CREAT|IPC_EXCL|0666);
   if(semid < 0){
      semid = semget(semkey,1,IPC_CREAT|0666);
   }
   else{
      semctl(semid,0,SETVAL,1);
   }
   buf.sem_num = 0;
   buf.sem_flg = 0;
   fd = shm_open("/shared_memory", O_RDWR, 0666);//O_RDONLY->O_RDWR
   if(fd == -1){  
      fprintf(stderr, "shm_open failed\n");
      exit(1);
   }
   p = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
   if(p == MAP_FAILED){ perror("mmap"); return 1;}
   while(1){
      buf.sem_op = -2;
      semop(semid, &buf, 1);
      fprintf(stderr,"-%s-\n",p);
      ret1 = strcmp(p,"exit");
      if(ret1 == 0) break;

      n = strlen(p);
      snprintf(count,sizeof(count),"%d",n);
      fprintf(stderr,"%s\n",count);
      strncpy(p,count,4096);
      /*fprintf(stderr,"+%s+\n",p);
      */buf.sem_op = 1;
      semop(semid,&buf,1);
   }

   if(munmap(p,sizeof(char)) == -1){ perror("munmap"); }
   //if(semctl(semid,0,IPC_RMID)!=0){ perror("semctl"); }
   close(fd);
   shm_unlink("/shared_memory");
   return 0;
}
/*
[sasayama@localhost Syoseki]$ ./mmap2_r_sem 
-Apple-
5
-Ball-
4
-exit-

ipcs -s
ipcrm -s 131073
------ セマフォ配列 --------
キー     semid      所有者  権限     nsems     
0x6102bc13 819200     sasayama   666        1 
 */

