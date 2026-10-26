
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
#define ITEMS 20

int buffer[SIZE], in = 0, out = 0;
sem_t emptySlots, fullSlots;
pthread_mutex_t mutex;

void *producer(void *arg) {
    (void)arg;
    for (int item = 1; item <= ITEMS; item++) {
        sem_wait(&emptySlots);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        in = (in + 1) % SIZE;
        printf("Produced: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&fullSlots);
    }
    return NULL;
}

void *consumer(void *arg) {
    (void)arg;
    for (int i = 0; i < ITEMS; i++) {
        sem_wait(&fullSlots);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        out = (out + 1) % SIZE;
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&emptySlots);
    }
    return NULL;
}

int main(void) {
    pthread_t p, c;

    sem_init(&emptySlots, 0, SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&mutex);
    return 0;
}

