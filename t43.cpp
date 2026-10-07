#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

    int fd[2];

    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {

        close(fd[1]);

        char buffer[100];

        read(
            fd[0],
            buffer,
            sizeof(buffer)
        );

        cout << "Child read from pipe: "
             << buffer << endl;

        close(fd[0]);
    }

    else {

        close(fd[0]);

        const char message[] =
            "Hello Child from Kernel Pipe";

        write(
            fd[1],
            message,
            sizeof(message)
        );

        close(fd[1]);

        wait(NULL);
    }

    return 0;
}
