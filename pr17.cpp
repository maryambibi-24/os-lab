
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ucontext.h>
#include <unistd.h>

#define STACK 65536

ucontext_t aCtx, bCtx, mainCtx;
char stackA[STACK], stackB[STACK];
volatile int stop = 0;

void userB(void) {
    for (int i = 0; i < 10; i++) {
        printf("User thread B counter = %d\n", i);
        swapcontext(&bCtx, &aCtx);
    }
    setcontext(&mainCtx);
}

void userA(void) {
    char ch;
    printf("User thread A: type one character and press Enter:\n");
    read(STDIN_FILENO, &ch, 1);
    printf("User thread A received input.\n");
    swapcontext(&aCtx, &bCtx);
    setcontext(&mainCtx);
}

void *reader(void *p) {
    (void)p;
    char ch;
    printf("Reader pthread: type one character and press Enter:\n");
    read(STDIN_FILENO, &ch, 1);
    printf("Reader pthread received input.\n");
    stop = 1;
    return NULL;
}

void *counter(void *p) {
    (void)p;
    int i = 0;
    while (!stop && i < 20) {
        printf("Counter pthread = %d\n", i++);
        usleep(300000);
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s user|kernel\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "user") == 0) {
        getcontext(&aCtx);
        aCtx.uc_stack.ss_sp = stackA;
        aCtx.uc_stack.ss_size = sizeof(stackA);
        aCtx.uc_link = &mainCtx;
        makecontext(&aCtx, userA, 0);

        getcontext(&bCtx);
        bCtx.uc_stack.ss_sp = stackB;
        bCtx.uc_stack.ss_size = sizeof(stackB);
        bCtx.uc_link = &mainCtx;
        makecontext(&bCtx, userB, 0);

        swapcontext(&mainCtx, &aCtx);
    } else {
        pthread_t r, c;
        pthread_create(&r, NULL, reader, NULL);
        pthread_create(&c, NULL, counter, NULL);
        pthread_join(r, NULL);
        stop = 1;
        pthread_join(c, NULL);
    }

    return 0;
}

