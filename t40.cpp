#include <iostream>
#include <queue>
#include <pthread.h>

using namespace std;

queue<int> buffer;

const int CAPACITY = 3;

pthread_mutex_t mtx =
    PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cv_producer =
    PTHREAD_COND_INITIALIZER;

pthread_cond_t cv_consumer =
    PTHREAD_COND_INITIALIZER;


void* producer(void* arg) {

    for (int item = 1; item <= 5; item++) {

        pthread_mutex_lock(&mtx);

        while (buffer.size() == CAPACITY) {

            pthread_cond_wait(
                &cv_producer,
                &mtx
            );
        }

        buffer.push(item);

        cout << "Produced: "
             << item << endl;

        pthread_cond_signal(&cv_consumer);

        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}


void* consumer(void* arg) {

    for (int i = 1; i <= 5; i++) {

        pthread_mutex_lock(&mtx);

        while (buffer.empty()) {

            pthread_cond_wait(
                &cv_consumer,
                &mtx
            );
        }

        int item = buffer.front();

        buffer.pop();

        cout << "Consumed: "
             << item << endl;

        pthread_cond_signal(&cv_producer);

        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}


int main() {

    pthread_t producer_thread;
    pthread_t consumer_thread;

    pthread_create(
        &producer_thread,
        NULL,
        producer,
        NULL
    );

    pthread_create(
        &consumer_thread,
        NULL,
        consumer,
        NULL
    );

    pthread_join(
        producer_thread,
        NULL
    );

    pthread_join(
        consumer_thread,
        NULL
    );

    pthread_mutex_destroy(&mtx);

    pthread_cond_destroy(&cv_producer);
    pthread_cond_destroy(&cv_consumer);

    return 0;
}
