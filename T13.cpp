#include <iostream>
#include <thread>
#include <barrier>
#include <vector>
using namespace std;

const int NUM_THREADS = 3;

barrier sync_point(NUM_THREADS);

void worker(int id)
{
    cout << "Thread " << id
         << " completed Phase 1." << endl;

    sync_point.arrive_and_wait();

    cout << "Thread " << id
         << " started Phase 2." << endl;
}

int main()
{
    vector<thread> threads;

    for (int i = 1; i <= NUM_THREADS; i++)
    {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
