
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <unistd.h>
#include <sys/syscall.h>

#define K 4
#define STACK_SIZE 65536
#define ROUNDS 5

ucontext_t ctx[K], mainCtx;
char stacks[K][STACK_SIZE];
int finished[K] = {0};
int current = 0;

void yield(void) {
    int previous = current;
    do {
        current = (current + 1) % K;
    } while (finished[current]);

    swapcontext(&ctx[previous], &ctx[current]);
}

void threadMain(int id) {
    for (int i = 1; i <= ROUNDS; i++) {
        printf("User thread %d, round %d, PID=%d, TID=%ld\n",
               id, i, getpid(), syscall(SYS_gettid));
        yield();
    }
    finished[id] = 1;

    int allDone = 1;
    for (int i = 0; i < K; i++)
        if (!finished[i]) allDone = 0;

    if (allDone) setcontext(&mainCtx);
    yield();
}

int main(void) {
    for (int i = 0; i < K; i++) {
        getcontext(&ctx[i]);
        ctx[i].uc_stack.ss_sp = stacks[i];
        ctx[i].uc_stack.ss_size = sizeof(stacks[i]);
        ctx[i].uc_link = &mainCtx;
        makecontext(&ctx[i], (void (*)(void))threadMain, 1, i);
    }

    current = 0;
    swapcontext(&mainCtx, &ctx[0]);
    printf("All user-level threads finished.\n");
    return 0;
}

