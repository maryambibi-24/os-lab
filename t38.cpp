#include <iostream>
#include <pthread.h>

using namespace std;

int counter = 0;

void* increment_task(void* arg) {

    for (int i = 1; i <= 100000; i++) {

        counter = counter + 1;
    }

    return NULL;
}

int main() {

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(
        &thread1,
        NULL,
        increment_task,
        NULL
    );

    pthread_create(
        &thread2,
        NULL,
        increment_task,
        NULL
    );

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    cout << "Expected: 200000 | Actual counter: "
         << counter << endl;

    return 0;
}
