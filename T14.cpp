#include <iostream>
#include <thread>
#include <latch>
#include <vector>
using namespace std;

latch start_flag(1);

void worker(int id)
{
    cout << "Worker " << id
         << " waiting..." << endl;

    start_flag.wait();

    cout << "Worker " << id
         << " running benchmark." << endl;
}

int main()
{
    vector<thread> workers;

    for (int i = 1; i <= 3; i++)
    {
        workers.emplace_back(worker, i);
    }

    cout << "Main thread preparing shared memory..." << endl;

    start_flag.count_down();

    for (auto& t : workers)
    {
        t.join();
    }

    return 0;
}
