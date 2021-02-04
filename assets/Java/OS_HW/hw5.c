#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_MESSAGE 64
char buffer[BUFFER_SIZE][MAX_MESSAGE];
int in = 0, out = 0, count = 0;

pthread_mutex_t mutex;
sem_t empty,full;

int repeat = 1;

void DisplayBuffer()
{
    printf("Buffer contents:\n");
    printf("\tcount = %d, in = %d, out = %d\n", count,in,out);
    
    int p = out;
    for(int i = 0; i < count; i++){
        printf("\t%d] %s\n", p, buffer[p]);
        p = (p + 1) % BUFFER_SIZE; 
    }
}
void* producer(void *param);
void* consumer(void *param);
int main(int argc, char *argv[])
{
    int duration = 30;
    if(argc == 2)
		duration = atoi(argv[1]);

    //initialize  mutext,full,empty
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    DisplayBuffer();
    
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    sleep(duration);
    repeat = 0;

    int value;
    sem_getvalue(&full,&value);
    if(value == 0) sem_post(&full);
    sem_getvalue(&empty,&value);
    if(value == 0) sem_post(&empty);
    
    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("Bye!\n");
    return 0;
}
void *producer(void *param)
{
    int no_messages = 10;
    char *messages[64] = {
        "Nice to see you!",
        "Aal izz well!",
        "I love you!God loves you!",
        "God loves you and has a wonderful plan for your life.",
        "God bless you!",
        "You are genius!",
        "Cheer up!",
        "Everything is gonna be okay.",
        "You are so precious!",
        "Hakuna matata!"
    };

    while(repeat==1)
    {
        sleep(rand()%3+1);
        int idx = rand()%10;
        printf("[Producer] Created a message \"%s\"\n", messages[idx]);
        
        //entry section
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);        
        
        //critical section
        printf("-------------------PRODUCER-------------------\n");
        printf("Producer is entering critical section.\n");
        printf("[Producer] \"%s\" ==> buffer\n", messages[idx]);
        strcpy(buffer[in],messages[idx]);
        in = (in+1)%BUFFER_SIZE;
        count++;
        DisplayBuffer();
        printf("Producer is leaving critical section.\n");
        printf("----------------------------------------------\n");

        //exit section
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *param)
{
    while(repeat==1)
    {   
        char nextc[MAX_MESSAGE] = {0,};

        //entry section
        sem_wait(&full);
        pthread_mutex_lock(&mutex);   

        //critical section
        printf("-------------------CONSUMER-------------------\n");
        printf("Consumer is entering critical section.\n");
        strcpy(nextc,buffer[out]);
        out = (out + 1) % BUFFER_SIZE; 
        count--;
        printf("[Consumer] buffer ==> \"%s\" \n",nextc);
        DisplayBuffer();
        printf("Consumer is leaving critical section.\n");
        printf("----------------------------------------------\n");

        //exit section
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("[Consumer] Consumed a message \"%s\" \n", nextc);
        sleep(rand()%3+2);
    }
}
