
#include <stdio.h>
#include <omp.h>

void taskX(void) {
    long long sum = 0;
    for (long long i = 0; i < 80000000LL; i++) sum += i % 17;
    printf("Task X finished; result = %lld\n", sum);
}

void taskY(void) {
    long long sum = 0;
    for (long long i = 0; i < 80000000LL; i++) sum += i % 23;
    printf("Task Y finished; result = %lld\n", sum);
}

int main(void) {
    double start = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        taskX();

        #pragma omp section
        taskY();
    }

    printf("Elapsed wall time: %.6f seconds\n",
           omp_get_wtime() - start);
    return 0;
}

