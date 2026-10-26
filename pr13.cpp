
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 5000000
#define MAXT 8

long long *a, partial[MAXT];

typedef struct { int id, t; } Arg;

void *sumWorker(void *p) {
    Arg *x = p;
    int lo = x->id * N / x->t;
    int hi = (x->id + 1) * N / x->t;
    long long s = 0;
    for (int i = lo; i < hi; i++) s += a[i];
    partial[x->id] = s;
    return NULL;
}

double elapsed(struct timespec a, struct timespec b) {
    return b.tv_sec - a.tv_sec + (b.tv_nsec - a.tv_nsec) / 1e9;
}

int main(void) {
    a = malloc(N * sizeof(long long));
    if (!a) return 1;
    for (int i = 0; i < N; i++) a[i] = i % 100;

    double t1 = 0;
    for (int t = 1; t <= MAXT; t++) {
        pthread_t th[t];
        Arg args[t];
        struct timespec s, e;
        clock_gettime(CLOCK_MONOTONIC, &s);

        for (int i = 0; i < t; i++) {
            args[i] = (Arg){i, t};
            pthread_create(&th[i], NULL, sumWorker, &args[i]);
        }
        long long sum = 0;
        for (int i = 0; i < t; i++) {
            pthread_join(th[i], NULL);
            sum += partial[i];
        }

        clock_gettime(CLOCK_MONOTONIC, &e);
        double time = elapsed(s, e);
        if (t == 1) t1 = time;

        printf("T=%d sum=%lld time=%.6f speedup=%.3f efficiency=%.3f\n",
               t, sum, time, t1 / time, (t1 / time) / t);
    }

    free(a);
    return 0;
}

