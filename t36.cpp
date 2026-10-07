#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

    pid_t pid = fork();

    if (pid == 0) {

        cout << "Child replacing its binary with '/bin/ls'..."
             << endl;

        char *args[] = {
            (char*)"ls",
            (char*)"-l",
            NULL
        };

        execvp(args[0], args);

        cout << "This line never executes if execvp succeeds!"
             << endl;
    }

    else {

        wait(NULL);

        cout << "Parent reaped replaced child image"
             << endl;
    }

    return 0;
}
