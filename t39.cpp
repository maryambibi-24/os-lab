#include <iostream>
#include <pthread.h>

using namespace std;

int counter = 0;

pthread_mutex_t mtx =
    PTHREAD_MUTEX_INITIALIZER;

void* safe_increment(void* arg) {

    for (int i = 1; i <= 100000; i++) {

        pthread_mutex_lock(&mtx);

        counter = counter + 1;

        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

int main() {

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(
        &thread1,
        NULL,
        safe_increment,
        NULL
    );

    pthread_create(
        &thread2,
        NULL,
        safe_increment,
        NULL
    );

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    cout << "Final counter with Mutex: "
         << counter << endl;

    pthread_mutex_destroy(&mtx);

    return 0;
}
