
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main(void) {
    int *a = malloc(N * sizeof(int));
    if (!a) return 1;

    for (int i = 0; i < N; i++)
        a[i] = (i * 7919) % 1000003;

    double start = omp_get_wtime();
    int maxSeq = a[0];
    for (int i = 1; i < N; i++)
        if (a[i] > maxSeq) maxSeq = a[i];
    double seqTime = omp_get_wtime() - start;

    int maxPar = a[0];
    start = omp_get_wtime();

    #pragma omp parallel for reduction(max:maxPar)
    for (int i = 0; i < N; i++)
        if (a[i] > maxPar) maxPar = a[i];

    double parTime = omp_get_wtime() - start;

    printf("Sequential max: %d (%.6f s)\n", maxSeq, seqTime);
    printf("Parallel max:   %d (%.6f s)\n", maxPar, parTime);
    printf("Correct: %s\n", maxSeq == maxPar ? "YES" : "NO");

    free(a);
    return 0;
}

