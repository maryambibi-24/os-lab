
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <pthread.h>
#include <ucontext.h>
#include <time.h>

#define COUNT 10000
#define STACK 65536

ucontext_t mainCtx, ctxA, ctxB;
char stackA[STACK], stackB[STACK];
volatile int switches = 0;

double now(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec / 1e9;
}

void *empty(void *p) {
    (void)p;
    return NULL;
}

void contextB(void) {
    while (switches < COUNT) {
        switches++;
        swapcontext(&ctxB, &ctxA);
    }
    setcontext(&mainCtx);
}

void contextA(void) {
    while (switches < COUNT) {
        swapcontext(&ctxA, &ctxB);
    }
    setcontext(&mainCtx);
}

int main(void) {
    double start = now();

    for (int i = 0; i < COUNT; i++) {
        pthread_t t;
        pthread_create(&t, NULL, empty, NULL);
        pthread_join(t, NULL);
    }
    double pthreadTime = now() - start;

    switches = 0;
    getcontext(&ctxA);
    ctxA.uc_stack.ss_sp = stackA;
    ctxA.uc_stack.ss_size = sizeof(stackA);
    ctxA.uc_link = &mainCtx;
    makecontext(&ctxA, contextA, 0);

    getcontext(&ctxB);
    ctxB.uc_stack.ss_sp = stackB;
    ctxB.uc_stack.ss_size = sizeof(stackB);
    ctxB.uc_link = &mainCtx;
    makecontext(&ctxB, contextB, 0);

    start = now();
    swapcontext(&mainCtx, &ctxA);
    double contextTime = now() - start;

    printf("Create/join %d pthreads: %.6f s\n", COUNT, pthreadTime);
    printf("User-context switching:   %.6f s\n", contextTime);
    if (contextTime > 0)
        printf("Time ratio: %.2f\n", pthreadTime / contextTime);

    return 0;
}

