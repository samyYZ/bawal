#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 10
int buffer[SIZE], counter = 0, readerCount = 0;
sem_t mutex, db;
pthread_t r[20], w[20];

void *writer(void *id){
    sem_wait(&db);
    int item = rand() % 100;
    buffer[counter++] = item;
    printf("Writer %d wrote %d\n", *(int*)id, item);
    sleep(1);
    sem_post(&db);
    return NULL;
}

void *reader(void *id){
    sem_wait(&mutex);
    readerCount++;
    if(readerCount == 1) sem_wait(&db);
    sem_post(&mutex);

    printf("Reader %d read %d\n", *(int*)id, buffer[counter-1]);
    sleep(1);

    sem_wait(&mutex);
    readerCount--;
    if(readerCount == 0) sem_post(&db);
    sem_post(&mutex);
    return NULL;
}

int main(){
    sem_init(&mutex,0,1);
    sem_init(&db,0,1);

    int nr, nw;
    printf("Enter no. of readers: ");
    scanf("%d",&nr);
    printf("Enter no. of writers: ");
    scanf("%d",&nw);

    int i;
    for(i=0;i<nw;i++) pthread_create(&w[i],NULL,writer,&i);
    for(i=0;i<nr;i++) pthread_create(&r[i],NULL,reader,&i);
    for(i=0;i<nw;i++) pthread_join(w[i],NULL);
    for(i=0;i<nr;i++) pthread_join(r[i],NULL);

    sem_destroy(&mutex);
    sem_destroy(&db);
    return 0;
}
