
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000000
#define MAX_THREADS 8

long long arr[N];
long long partial[MAX_THREADS];
int T;

double getTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void *worker(void *arg) {
    long id = (long)arg;

    int chunk = (N + T - 1) / T;
    int start = id * chunk;
    int end = start + chunk;

    if (end > N)
        end = N;

    long long sum = 0;

    for (int i = start; i < end; i++)
        sum += arr[i];

    partial[id] = sum;

    return NULL;
}

int main() {
    for (int i = 0; i < N; i++)
        arr[i] = i % 100;

    double start = getTime();

    long long sequentialSum = 0;

    for (int i = 0; i < N; i++)
        sequentialSum += arr[i];

    double sequentialTime = getTime() - start;

    printf("Sequential Sum = %lld\n", sequentialSum);
    printf("Sequential Time = %.6f seconds\n", sequentialTime);

    for (T = 1; T <= MAX_THREADS; T *= 2) {
        pthread_t threads[MAX_THREADS];

        start = getTime();

        for (long i = 0; i < T; i++)
            pthread_create(&threads[i], NULL, worker, (void *)i);

        for (int i = 0; i < T; i++)
            pthread_join(threads[i], NULL);

        long long parallelSum = 0;

        for (int i = 0; i < T; i++)
            parallelSum += partial[i];

        double parallelTime = getTime() - start;

        printf("\nThreads = %d\n", T);
        printf("Parallel Sum = %lld\n", parallelSum);
        printf("Parallel Time = %.6f seconds\n", parallelTime);
        printf("Speedup = %.2f\n", sequentialTime / parallelTime);
    }

    return 0;
}

