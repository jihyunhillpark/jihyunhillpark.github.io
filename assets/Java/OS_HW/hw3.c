/*
Author  : jihyun Park
Date    : 2020.04.05
Purpose : OS Practice - Write a messenger using message passing on Ubuntu Linux (Google cloud or VirtualBox) using vim and gcc.
Title   : practice - IPC mesage passing using message passing and distribute sending and receiving task to each two thread.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define SIZE 1024

int repeat_receiver=1;

typedef struct {
   long  data_type;
   char  data_buff[SIZE];
}t_data;

void* receiver(void *);
void* sender(void *);

int main(int argc, char *argv[])
{
	if(argc != 3)
	{	
		printf("Usage : %s <snd_key> <rcv_key>\n", argv[0]);
		exit(0);
	}
	pthread_t p_thread[2];
	int thr_id, ret;
	int snd_key = atoi(argv[1]);
	int rcv_key = atoi(argv[2]);
	int snd_queue, rcv_queue;
	
	printf("snd_key = %d, rcv_key = %d\n", snd_key, rcv_key);
	snd_queue = msgget((key_t)snd_key, IPC_CREAT | 0666);
	rcv_queue = msgget((key_t)rcv_key, IPC_CREAT | 0666);
	
	thr_id = pthread_create(&p_thread[0],NULL,sender, &snd_queue);
	if (thr_id < 0)
	{
		perror("Thread create error : ");
		exit(0);
	
	}
    thr_id = pthread_create(&p_thread[1],NULL, receiver, &rcv_queue);
	if (thr_id < 0)
	{   
		perror("Thread create error : ");
		exit(0);					        
	}
	pthread_join(p_thread[0],(void **)&ret);
	pthread_join(p_thread[1],(void **)&ret);

	msgctl(snd_queue,IPC_RMID,NULL );
	msgctl(rcv_queue,IPC_RMID,NULL );

	return 0;
}
void *sender(void *snd_queue)
{
	t_data snd_data;

	while(1)
	{
		printf("[msg] ");

		snd_data.data_type = 1;
		fgets(snd_data.data_buff,SIZE, stdin);
		snd_data.data_buff[strlen(snd_data.data_buff)-1] = 0;

		if(strcmp(snd_data.data_buff,"quit")== 0)
		{	repeat_receiver = 0;	
			break;
		}
		msgsnd(*(int *)snd_queue, &snd_data,sizeof(t_data)-sizeof(long),0);
		fflush(stdin);
	}
}
void *receiver(void *rcv_queue)
{
	t_data rcv_data;
	
	fflush(stdout);
	while(repeat_receiver)
	{
		rcv_data.data_buff[0] =0;
		msgrcv(*(int *)rcv_queue, &rcv_data, sizeof(t_data)-sizeof(long), 1, IPC_NOWAIT);

		if(strlen(rcv_data.data_buff)!= 0)
		{
			//rcv_data.data_buff[strlen(rcv_data.data_buff)-1] = '\n';
			printf("\t\t\t\t\t\t[incoming] %s\n[msg] ",rcv_data.data_buff);
		}
		usleep(1000);
		fflush(stdout);
	}
	fflush(stdout);
}
