#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int shared_counter = 100;

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        shared_counter = shared_counter + 50;

        cout << "Child sees shared_counter = "
             << shared_counter << endl;
    }

    else {

        wait(NULL);

        cout << "Parent sees shared_counter = "
             << shared_counter << endl;
    }

    return 0;
}
