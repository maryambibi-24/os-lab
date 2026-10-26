
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define T 4

typedef struct { int milliseconds; } Job;

void busy_ms(int ms) {
    struct timespec start, now;
    clock_gettime(CLOCK_MONOTONIC, &start);

    do {
        for (volatile int i = 0; i < 10000; i++);
        clock_gettime(CLOCK_MONOTONIC, &now);
    } while ((now.tv_sec - start.tv_sec) * 1000.0 +
             (now.tv_nsec - start.tv_nsec) / 1000000.0 < ms);
}

void *worker(void *p) {
    Job *j = p;
    busy_ms(j->milliseconds);
    return NULL;
}

double run(int times[T]) {
    pthread_t th[T];
    Job jobs[T];
    struct timespec a, b;
    clock_gettime(CLOCK_MONOTONIC, &a);

    for (int i = 0; i < T; i++) {
        jobs[i].milliseconds = times[i];
        pthread_create(&th[i], NULL, worker, &jobs[i]);
    }
    for (int i = 0; i < T; i++) pthread_join(th[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &b);
    return (b.tv_sec - a.tv_sec) +
           (b.tv_nsec - a.tv_nsec) / 1e9;
}

int main(void) {
    int unbalanced[T] = {100, 400, 100, 400};
    int balanced[T] = {250, 250, 250, 250};

    printf("Unequal workloads: %.3f seconds\n", run(unbalanced));
    printf("Balanced workloads: %.3f seconds\n", run(balanced));
    return 0;
}

