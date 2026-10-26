
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 5000000
#define TMAX 8

long long *a;
long long partial[TMAX];

typedef struct { int id, threads, start; } Arg;

void *worker(void *p) {
    Arg *x = p;
    int begin = x->start + (N - x->start) * x->id / x->threads;
    int end = x->start + (N - x->start) * (x->id + 1) / x->threads;
    long long sum = 0;
    for (int i = begin; i < end; i++) sum += a[i];
    partial[x->id] = sum;
    return NULL;
}

double seconds(struct timespec a, struct timespec b) {
    return b.tv_sec - a.tv_sec + (b.tv_nsec - a.tv_nsec) / 1e9;
}

int main(void) {
    a = malloc(N * sizeof(long long));
    if (!a) return 1;
    for (int i = 0; i < N; i++) a[i] = i % 100;

    struct timespec s, e;
    clock_gettime(CLOCK_MONOTONIC, &s);
    long long total = 0;
    for (int i = 0; i < N; i++) total += a[i];
    clock_gettime(CLOCK_MONOTONIC, &e);
    double seqTime = seconds(s, e);
    printf("Sequential sum: %lld, time %.6f s\n", total, seqTime);

    int serialEnd = N / 10;
    for (int t = 1; t <= TMAX; t *= 2) {
        clock_gettime(CLOCK_MONOTONIC, &s);

        long long serial = 0;
        for (int i = 0; i < serialEnd; i++) serial += a[i];

        pthread_t th[t];
        Arg args[t];
        for (int i = 0; i < t; i++) {
            args[i] = (Arg){i, t, serialEnd};
            pthread_create(&th[i], NULL, worker, &args[i]);
        }
        long long parallel = 0;
        for (int i = 0; i < t; i++) {
            pthread_join(th[i], NULL);
            parallel += partial[i];
        }

        clock_gettime(CLOCK_MONOTONIC, &e);
        double elapsed = seconds(s, e);
        double measured = seqTime / elapsed;
        double predicted = 1.0 / (0.10 + 0.90 / t);

        printf("T=%d sum=%lld time=%.6f speedup=%.3f predicted=%.3f\n",
               t, serial + parallel, elapsed, measured, predicted);
    }

    free(a);
    return 0;
}

