
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define N 1000000
#define T 4

double A[N], B[N], Cseq[N], Cpar[N];
typedef struct { int id; } Arg;

void *worker(void *p) {
    int id = ((Arg *)p)->id;
    int start = id * N / T;
    int end = (id + 1) * N / T;

    for (int i = start; i < end; i++)
        Cpar[i] = A[i] * B[i] + sin(A[i]);

    return NULL;
}

double now(void) {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main(void) {
    pthread_t th[T];
    Arg args[T];

    for (int i = 0; i < N; i++) {
        A[i] = i * 0.001;
        B[i] = i * 0.002;
    }

    double t = now();
    for (int i = 0; i < N; i++)
        Cseq[i] = A[i] * B[i] + sin(A[i]);
    double seqTime = now() - t;

    t = now();
    for (int i = 0; i < T; i++) {
        args[i].id = i;
        pthread_create(&th[i], NULL, worker, &args[i]);
    }
    for (int i = 0; i < T; i++) pthread_join(th[i], NULL);
    double parTime = now() - t;

    int correct = 1;
    for (int i = 0; i < N; i++)
        if (fabs(Cseq[i] - Cpar[i]) > 1e-9) {
            correct = 0;
            break;
        }

    printf("Elements: %d, Threads: %d\n", N, T);
    printf("Sequential time: %.6f s\n", seqTime);
    printf("Parallel time:   %.6f s\n", parTime);
    printf("Results match: %s\n", correct ? "YES" : "NO");
    return 0;
}

