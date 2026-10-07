#include <iostream>
#include <pthread.h>

using namespace std;

int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int vector_data[3] = {1, 2, 3};
int result[3];

void* worker_multiply_row(void* arg) {

    int row_idx = *(int*)arg;

    int sum = 0;

    for (int col = 0; col < 3; col++) {

        sum = sum +
              matrix[row_idx][col] * vector_data[col];
    }

    result[row_idx] = sum;

    return NULL;
}

int main() {

    pthread_t thread_list[3];

    int rows[3] = {0, 1, 2};

    for (int i = 0; i < 3; i++) {

        pthread_create(
            &thread_list[i],
            NULL,
            worker_multiply_row,
            &rows[i]
        );
    }

    for (int i = 0; i < 3; i++) {

        pthread_join(
            thread_list[i],
            NULL
        );
    }

    cout << "Result Vector: [";

    for (int i = 0; i < 3; i++) {

        cout << result[i];

        if (i < 2)
            cout << ", ";
    }

    cout << "]" << endl;

    return 0;
}
