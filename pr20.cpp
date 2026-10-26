
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>

#define USER_TASKS 20
#define CARRIERS 2

void *carrier(void *arg) {
    int carrierID = *(int *)arg;

    /* Each carrier manages 10 cooperative user-task simulations. */
    for (int round = 0; round < 5; round++) {
        for (int task = carrierID; task < USER_TASKS; task += CARRIERS) {
            printf("Carrier %d runs user task %d, round %d\n",
                   carrierID, task, round + 1);
            sched_yield();
        }
    }
    return NULL;
}

typedef struct {
    long iterations;
} Work;

void *cpuWorker(void *arg) {
    Work *w = arg;
    volatile unsigned long long value = 0;

    for (long i = 0; i < w->iterations; i++)
        value += (unsigned long long)i % 97;

    return NULL;
}

double now(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec / 1e9;
}

double benchmark(int count, long iterations) {
    pthread_t *threads = malloc(count * sizeof(pthread_t));
    Work *work = malloc(count * sizeof(Work));

    if (!threads || !work) {
        free(threads);
        free(work);
        return -1;
    }

    double start = now();

    for (int i = 0; i < count; i++) {
        work[i].iterations = iterations;
        if (pthread_create(&threads[i], NULL, cpuWorker, &work[i]) != 0) {
            fprintf(stderr, "Could not create worker thread.\n");
            exit(1);
        }
    }

    for (int i = 0; i < count; i++)
        pthread_join(threads[i], NULL);

    double duration = now() - start;
    free(threads);
    free(work);
    return duration;
}

int main(void) {
    printf("PART A: M:N-style carrier demonstration\n");

    pthread_t carriers[CARRIERS];
    int ids[CARRIERS];

    for (int i = 0; i < CARRIERS; i++) {
        ids[i] = i;
        pthread_create(&carriers[i], NULL, carrier, &ids[i]);
    }

    for (int i = 0; i < CARRIERS; i++)
        pthread_join(carriers[i], NULL);

    printf("\nPART B: CPU-bound oversubscription experiment\n");

    long cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (cores < 1) cores = 1;

    int normal = (int)cores;
    int excess = normal * 4;

    printf("Detected online CPU count: %ld\n", cores);
    printf("Running %d workers...\n", normal);
    double normalTime = benchmark(normal, 10000000L);

    printf("Running %d workers...\n", excess);
    double excessTime = benchmark(excess, 10000000L);

    printf("CPU-count workers: %.4f seconds\n", normalTime);
    printf("4x workers:         %.4f seconds\n", excessTime);

    if (normalTime > 0)
        printf("Oversubscribed/normal time ratio: %.3f\n",
               excessTime / normalTime);

    printf("\nPART C: Cooperative starvation concept\n");
    printf("If one user-level task never yields, tasks sharing its\n");
    printf("carrier cannot run until that task yields or finishes.\n");

    return 0;
}

