//
// Created by Anthony/Samiratu/Lhet on 11/14/19.
//

#include <stdio.h>
#include<pthread.h>
#include<zconf.h>
#include<semaphore.h>
#include <stdlib.h>


#define left i>0?(i-1)%numberofChopsticks:numberofChopsticks-1
#define right (i+1)%numberofChopsticks
#define thinking 0
#define hungry 1
#define eating 2
int numberofChopsticks;

int *state;
int *philosopher_num;
sem_t mutex;
sem_t *sem_phil;

void * philosopher(void *);
void takechops(int);
void insert(int);
void checkFree_chopsticks(int);

int main(int argc,char **argv)
{
    printf("Please enter the number of philosophers:\n");
    scanf("%d",&numberofChopsticks);

    state = malloc(sizeof *state *numberofChopsticks);
    philosopher_num= malloc(sizeof *philosopher_num *numberofChopsticks);
    sem_phil = malloc(sizeof *sem_phil *numberofChopsticks);

    int k;
    pthread_t tid[numberofChopsticks];
    printf("\nDining Phiosopher\n");
    for(k=0;k<numberofChopsticks;k++)
    {
        philosopher_num[k]=k;
    }
    sem_init(&mutex,0,1);
    for(k=0;k<numberofChopsticks;k++) sem_init(&sem_phil[k],0,0);
    for(k=0;k<numberofChopsticks;k++) pthread_create(&tid[k],NULL,philosopher,&philosopher_num[k]);
    for(k=0;k<numberofChopsticks;k++) pthread_join(tid[k],NULL);
}
void checkFree_chopsticks(int i) {
    if (state[i] == hungry && state[left] != eating && state[right] != eating) {
        state[i] = 2;
        printf("\nPhilosopher %d is eating\n", i);
        sem_post(&sem_phil[i]);
    }
}


void * philosopher(void *param)
{
    int i=*((int *)param);
    int taketime=3;
    int puttingtime=4;
    while(1)
    {
        sleep(taketime);
        takechops(i);
        sleep(puttingtime);
        insert(i);
    }
}
    void  takechops(int i){
    sem_wait(&mutex);
    state[i]=hungry;
    printf("\nPhilosopher %d is hungry\n",i);
    checkFree_chopsticks(i);
    sem_post(&mutex);
    sem_wait(&sem_phil[i]);
}

void insert(int i)
{
    sem_wait(&mutex);
    state[i]=thinking;
    printf("\nPhilosopher %d is thinking\n",i);
    checkFree_chopsticks(left);
    checkFree_chopsticks(right);
    sem_post(&mutex);
}