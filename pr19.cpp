
#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define T 4

void *worker(void *arg) {
    int id = *(int *)arg;
    long tid = syscall(SYS_gettid);

    printf("Worker %d: PID=%d, TID=%ld\n", id, getpid(), tid);
    sleep(30);
    return NULL;
}

int main(void) {
    pthread_t th[T];
    int ids[T];

    printf("Main process PID=%d, main TID=%ld\n",
           getpid(), syscall(SYS_gettid));
    fflush(stdout);

    for (int i = 0; i < T; i++) {
        ids[i] = i + 1;
        pthread_create(&th[i], NULL, worker, &ids[i]);
    }

    printf("Keep this program running for 30 seconds.\n");
    fflush(stdout);

    for (int i = 0; i < T; i++) pthread_join(th[i], NULL);
    return 0;
}

