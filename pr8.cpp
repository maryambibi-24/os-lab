
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5
#define N 20
#define END -1

typedef struct {
    int data[SIZE], in, out;
    sem_t empty, full;
    pthread_mutex_t lock;
} Queue;

Queue q1, q2;

void initQueue(Queue *q) {
    q->in = q->out = 0;
    sem_init(&q->empty, 0, SIZE);
    sem_init(&q->full, 0, 0);
    pthread_mutex_init(&q->lock, NULL);
}

void put(Queue *q, int x) {
    sem_wait(&q->empty);
    pthread_mutex_lock(&q->lock);
    q->data[q->in] = x;
    q->in = (q->in + 1) % SIZE;
    pthread_mutex_unlock(&q->lock);
    sem_post(&q->full);
}

int get(Queue *q) {
    sem_wait(&q->full);
    pthread_mutex_lock(&q->lock);
    int x = q->data[q->out];
    q->out = (q->out + 1) % SIZE;
    pthread_mutex_unlock(&q->lock);
    sem_post(&q->empty);
    return x;
}

void *stage1(void *arg) {
    (void)arg;
    for (int i = 1; i <= N; i++) put(&q1, i);
    put(&q1, END);
    return NULL;
}

void *stage2(void *arg) {
    (void)arg;
    while (1) {
        int x = get(&q1);
        if (x == END) {
            put(&q2, END);
            break;
        }
        put(&q2, x * x);
    }
    return NULL;
}

void *stage3(void *arg) {
    (void)arg;
    long long sum = 0;
    while (1) {
        int x = get(&q2);
        if (x == END) break;
        sum += x;
    }
    printf("Sum of squares from 1 to %d = %lld\n", N, sum);
    return NULL;
}

int main(void) {
    pthread_t a, b, c;
    initQueue(&q1);
    initQueue(&q2);

    pthread_create(&a, NULL, stage1, NULL);
    pthread_create(&b, NULL, stage2, NULL);
    pthread_create(&c, NULL, stage3, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);

    return 0;
}

