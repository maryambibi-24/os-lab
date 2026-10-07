#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>
using namespace std;

counting_semaphore<3> sem(3);

void task(int id)
{
    sem.acquire();

    cout << "Task " << id
         << " is using a resource." << endl;

    this_thread::sleep_for(chrono::seconds(2));

    cout << "Task " << id
         << " released the resource." << endl;

    sem.release();
}

int main()
{
    vector<thread> threads;

    for (int i = 1; i <= 6; i++)
    {
        threads.emplace_back(task, i);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
