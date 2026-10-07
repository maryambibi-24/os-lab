#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        cout << "Initial Parent PID: "
             << getppid() << endl;

        sleep(3);

        cout << "After parent dies, new Parent PID: "
             << getppid() << endl;

        exit(0);
    }

    else {

        cout << "Parent PID: " << getpid()
             << " exiting immediately" << endl;

        exit(0);
    }

    return 0;
}
