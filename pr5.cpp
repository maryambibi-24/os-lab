
#include <stdio.h>
#include <pthread.h>
#include <omp.h>

#define N 1000000
#define T 4

long long A[N], B[N], result = 0;
pthread_mutex_t lock;

void *race_worker(void *arg) {
    int id = *(int *)arg;
    int start = id * N / T, end = (id + 1) * N / T;
    for (int i = start; i < end; i++)
        result += A[i] * B[i];
    return NULL;
}

void *mutex_worker(void *arg) {
    int id = *(int *)arg;
    int start = id * N / T, end = (id + 1) * N / T;
    long long local = 0;
    for (int i = start; i < end; i++)
        local += A[i] * B[i];

    pthread_mutex_lock(&lock);
    result += local;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t th[T];
    int ids[T];
    long long expected = 0;

    for (int i = 0; i < N; i++) {
        A[i] = i % 100;
        B[i] = i % 50;
        expected += A[i] * B[i];
    }

    result = 0;
    for (int i = 0; i < T; i++) {
        ids[i] = i;
        pthread_create(&th[i], NULL, race_worker, &ids[i]);
    }
    for (int i = 0; i < T; i++) pthread_join(th[i], NULL);
    printf("Without protection: %lld (expected %lld)\n", result, expected);

    pthread_mutex_init(&lock, NULL);
    result = 0;
    for (int i = 0; i < T; i++)
        pthread_create(&th[i], NULL, mutex_worker, &ids[i]);
    for (int i = 0; i < T; i++) pthread_join(th[i], NULL);
    printf("With mutex:         %lld\n", result);

    long long ompResult = 0;
    #pragma omp parallel for reduction(+:ompResult)
    for (int i = 0; i < N; i++)
        ompResult += A[i] * B[i];
    printf("OpenMP reduction:   %lld\n", ompResult);

    pthread_mutex_destroy(&lock);
    return 0;
}

