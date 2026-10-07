#include <iostream>
#include <pthread.h>

using namespace std;

int shared_data = 0;

pthread_rwlock_t rw_lock =
    PTHREAD_RWLOCK_INITIALIZER;


void* reader(void* arg) {

    int id = *(int*)arg;

    pthread_rwlock_rdlock(&rw_lock);

    cout << "Reader " << id
         << " read value: "
         << shared_data << endl;

    pthread_rwlock_unlock(&rw_lock);

    return NULL;
}


void* writer(void* arg) {

    int* data = (int*)arg;

    int id = data[0];
    int value = data[1];

    pthread_rwlock_wrlock(&rw_lock);

    shared_data = value;

    cout << "Writer " << id
         << " updated value to: "
         << shared_data << endl;

    pthread_rwlock_unlock(&rw_lock);

    return NULL;
}


int main() {

    pthread_t thread;

    int writer1[2] = {1, 42};

    pthread_create(
        &thread,
        NULL,
        writer,
        writer1
    );

    pthread_join(thread, NULL);


    int reader1 = 1;

    pthread_create(
        &thread,
        NULL,
        reader,
        &reader1
    );

    pthread_join(thread, NULL);


    int reader2 = 2;

    pthread_create(
        &thread,
        NULL,
        reader,
        &reader2
    );

    pthread_join(thread, NULL);


    int writer2[2] = {2, 99};

    pthread_create(
        &thread,
        NULL,
        writer,
        writer2
    );

    pthread_join(thread, NULL);


    int reader3 = 3;

    pthread_create(
        &thread,
        NULL,
        reader,
        &reader3
    );

    pthread_join(thread, NULL);

    pthread_rwlock_destroy(&rw_lock);

    return 0;
}
