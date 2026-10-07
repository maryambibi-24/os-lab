#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutexA =
    PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutexB =
    PTHREAD_MUTEX_INITIALIZER;


void* thread1_work(void* arg) {

    pthread_mutex_lock(&mutexA);

    cout << "Thread 1 acquired Lock A, "
         << "waiting for Lock B ..." << endl;

    sleep(1);

    pthread_mutex_lock(&mutexB);

    pthread_mutex_unlock(&mutexB);

    pthread_mutex_unlock(&mutexA);

    return NULL;
}


void* thread2_work(void* arg) {

    pthread_mutex_lock(&mutexB);

    cout << "Thread 2 acquired Lock B, "
         << "waiting for Lock A ..." << endl;

    sleep(1);

    pthread_mutex_lock(&mutexA);

    pthread_mutex_unlock(&mutexA);

    pthread_mutex_unlock(&mutexB);

    return NULL;
}


int main() {

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(
        &thread1,
        NULL,
        thread1_work,
        NULL
    );

    pthread_create(
        &thread2,
        NULL,
        thread2_work,
        NULL
    );

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutexA);
    pthread_mutex_destroy(&mutexB);

    return 0;
}
