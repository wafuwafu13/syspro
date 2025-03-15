#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
//shared memoryの入出力側Apple -> 5
int main(){
   char *p,line[4096],command[4096];
   int fd,ret1,ret2,ret3,tmp,i,semid;
   key_t semkey;
   struct sembuf buf;

   semkey = ftok("mmap2_r_sem",'a');
   semid = semget(semkey,1,IPC_CREAT|IPC_EXCL|0666);
   fprintf(stderr, "semid=%d\n",semid);
   if(semid < 0){
      semid = semget(semkey,1,IPC_CREAT|0666);
      fprintf(stderr, ">semid=%d\n",semid);
   }
   else{
      semctl(semid,0,SETVAL,1);
   }
   buf.sem_num = 0;
   buf.sem_flg = 0;

   fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
   if(fd == -1){ 
      fprintf(stderr, "shm_open failed\n");
      exit(1);
   }

   ret1 = ftruncate(fd,sizeof(line));

   p = mmap(0, sizeof(line), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
   if(p == MAP_FAILED){ perror("mmap"); return 1;}
   while(1){
      buf.sem_op = -1;
      semop(semid,&buf,1);
      fprintf(stderr,"> ");
      fgets(line,sizeof(line),stdin);
      ret2 = sscanf(line,"%[^\n]",command);
      if(ret2 < 0) break;
      ret3 = strcmp(command,"exit");
      strncpy(p,command,sizeof(command));
      buf.sem_op = 2;
      semop(semid,&buf,1);
      if(ret3 == 0) {
         break;
      }
      buf.sem_op = -1;
      semop(semid,&buf,1);
      fprintf(stderr,"=%s <-> %s=\n", command,p);
      buf.sem_op = 1;
      semop(semid,&buf,1);
   }

   if(munmap(p,sizeof(line)) == -1){ perror("munmap"); }
   if(semctl(semid,0,IPC_RMID) != 0){ perror("semctl"); } 
   close(fd);
   return 0;
}
// gcc -lrt
/*

[sasayama@localhost Syoseki]$ ./mmap2_s_sem 
> Apple
=Apple <-> 5=
> Ball
=Ball <-> 4=
> exit

 */

