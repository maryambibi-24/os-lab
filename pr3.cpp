
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 200
#define T 4

double A[N][N], B[N][N], Cseq[N][N], Cpar[N][N];

void *multiply(void *arg) {
    int id = *(int *)arg;
    int start = id * N / T;
    int end = (id + 1) * N / T;

    for (int i = start; i < end; i++)
        for (int j = 0; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];
            Cpar[i][j] = sum;
        }
    return NULL;
}

int main(void) {
    pthread_t th[T];
    int ids[T];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i == j ? 1 : 0;
        }

    clock_t start = clock();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            Cseq[i][j] = 0;
            for (int k = 0; k < N; k++)
                Cseq[i][j] += A[i][k] * B[k][j];
        }
    double seq = (double)(clock() - start) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < T; i++) {
        ids[i] = i;
        pthread_create(&th[i], NULL, multiply, &ids[i]);
    }
    for (int i = 0; i < T; i++) pthread_join(th[i], NULL);
    double par = (double)(clock() - start) / CLOCKS_PER_SEC;

    int correct = 1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (Cseq[i][j] != Cpar[i][j]) correct = 0;

    printf("Matrix size: %d x %d\n", N, N);
    printf("Sequential time: %.6f s\n", seq);
    printf("Parallel time: %.6f s\n", par);
    printf("Results match: %s\n", correct ? "YES" : "NO");
    return 0;
}

