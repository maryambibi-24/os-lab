
#include <stdio.h>
#include <pthread.h>
#include <time.h>

volatile unsigned long long sink;

void taskX(void) {
    unsigned long long s = 0;
    for (unsigned long long i = 0; i < 80000000ULL; i++)
        s += i % 17;
    sink = s;
}

void taskY(void) {
    unsigned long long s = 0;
    for (unsigned long long i = 0; i < 80000000ULL; i++)
        s += i % 23;
    sink = s;
}

void *runX(void *p) { (void)p; taskX(); return NULL; }
void *runY(void *p) { (void)p; taskY(); return NULL; }

double seconds(clock_t a, clock_t b) {
    return (double)(b - a) / CLOCKS_PER_SEC;
}

int main(void) {
    clock_t a = clock();
    taskX(); taskY();
    clock_t b = clock();
    printf("Sequential CPU time: %.3f s\n", seconds(a, b));

    pthread_t x, y;
    a = clock();
    pthread_create(&x, NULL, runX, NULL);
    pthread_create(&y, NULL, runY, NULL);
    pthread_join(x, NULL);
    pthread_join(y, NULL);
    b = clock();

    printf("Concurrent CPU time: %.3f s\n", seconds(a, b));
    return 0;
}

