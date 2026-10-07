#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

queue<function<void()>> tasks;

mutex queue_mtx;
condition_variable cv;

bool stop = false;

void worker(int id)
{
    while (true)
    {
        function<void()> task;

        {
            unique_lock<mutex> lock(queue_mtx);

            cv.wait(lock, [] {
                return stop || !tasks.empty();
            });

            if (stop && tasks.empty())
            {
                return;
            }

            task = move(tasks.front());
            tasks.pop();
        }

        cout << "Worker " << id << " executing task." << endl;

        task();
    }
}

int main()
{
    const int NUM_WORKERS = 3;

    vector<thread> workers;

    for (int i = 1; i <= NUM_WORKERS; i++)
    {
        workers.emplace_back(worker, i);
    }

    for (int i = 1; i <= 6; i++)
    {
        {
            lock_guard<mutex> lock(queue_mtx);

            tasks.push([i] {
                cout << "Task " << i << " is running." << endl;
            });
        }

        cv.notify_one();
    }

    {
        lock_guard<mutex> lock(queue_mtx);
        stop = true;
    }

    cv.notify_all();

    for (auto& t : workers)
    {
        t.join();
    }

    cout << "Thread pool stopped." << endl;

    return 0;
}
