#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <vector>
using namespace std;

int shared_data = 0;
shared_mutex rw_mtx;

void reader(int id)
{
    shared_lock<shared_mutex> lock(rw_mtx);

    cout << "Reader " << id
         << " reads data = "
         << shared_data << endl;
}

void writer(int id)
{
    unique_lock<shared_mutex> lock(rw_mtx);

    shared_data++;

    cout << "Writer " << id
         << " changed data to "
         << shared_data << endl;
}

int main()
{
    vector<thread> threads;

    threads.emplace_back(reader, 1);
    threads.emplace_back(reader, 2);

    threads.emplace_back(writer, 1);

    threads.emplace_back(reader, 3);

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
