#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        cout << "Child PID: " << getpid()
             << " terminating now" << endl;

        exit(0);
    }

    else {

        cout << "Parent sleeping for 10 s without wait(). "
             << "Inspect via 'ps -l'" << endl;

        sleep(10);

        wait(NULL);

        cout << "Parent cleaned up child. Exiting." << endl;
    }

    return 0;
}
