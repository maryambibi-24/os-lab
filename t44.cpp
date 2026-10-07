#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main() {

    int shm_fd;

    shm_fd = shm_open(
        "/shm_os_lab",
        O_CREAT | O_RDWR,
        0666
    );

    ftruncate(shm_fd, 1024);

    char* ptr = (char*)mmap(
        0,
        1024,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        shm_fd,
        0
    );

    pid_t pid = fork();

    if (pid == 0) {

        sleep(1);

        cout << "Child read from SHM: "
             << ptr << endl;
    }

    else {

        strcpy(
            ptr,
            "OS Shared Memory Payload"
        );

        wait(NULL);

        shm_unlink("/shm_os_lab");
    }

    return 0;
}
