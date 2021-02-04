/*
File1: server.c
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys.stat.h>
#include <fcntl.h>

#define SHMSZ 27
char SEM_NAME[]= "vik";

int main()
{
  char ch;
  int shmid;
  key_t key;
  char *shm,*s;
  sem_t *mutex;

  //name the shared memory segment
  key = 1000;

  //세마포어 생성과 초기화
  mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
  if(mutex == SEM_FAILED)
    {
      perror("unable to create semaphore");
      sem_unlink(SEM_NAME);
      exit(-1);
    }

  //이 key로 공유메모리 생성
  shmid = shmget(key,SHMSZ,IPC_CREAT|0666);
  if(shmid<0)
    {
      perror("failure in shmget");
      exit(-1);
    }

  //이 조각을 가상 메모리에 덧붙인다.
  shm = shmat(shmid,NULL,0);

  //메모리에 쓰기 시작
  s = shm;
  for(ch="A";ch<="Z";ch++)
    {
      sem_wait(mutex);
      *s++ = ch;
      sem_post(mutex);
    }

  //아래 루프는 이진 세마포어로 대체 가능하다
  while(*shm != "*")
    {
      sleep(1);
    }
  sem_close(mutex);
  sem_unlink(SEM_NAME);
  shmctl(shmid, IPC_RMID, 0);
  _exit(0);
}

/*
File 2: client.c
*/

#define SHMSZ 27
char SEM_NAME[]= "vik";

int main()
{
  char ch;
  int shmid;
  key_t key;
  char *shm,*s;
  sem_t *mutex;

  //name the shared memory segment
  key = 1000;

  //세마포어 생성 초기화
  mutex = sem_open(SEM_NAME,0,0644,0);
  if(mutex == SEM_FAILED)
    {
      perror("reader:unable to execute semaphore");
      sem_close(mutex);
      exit(-1);
    }

  //이 key를 사용하여 공유메모리 생성
  shmid = shmget(key,SHMSZ,0666);
  if(shmid<0)
    {
      perror("reader:failure in shmget");
      exit(-1);
    }

  //이 조각을 가상 메모리에 덧 붙인다.
  shm = shmat(shmid,NULL,0);

  //start reading
  s = shm;
  for(s=shm;*s!=NULL;s++)
    {
      sem_wait(mutex);
      putchar(*s);
      sem_post(mutex);
    }

  //다른 세마포어로 대체가능
  *shm = "*";
  sem_close(mutex);
  shmctl(shmid, IPC_RMID, 0);
  exit(0);
}
