#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtxA;
mutex mtxB;

void thread1()
{
    scoped_lock lock(mtxA, mtxB);

    cout << "Thread 1 acquired both locks." << endl;

    this_thread::sleep_for(chrono::milliseconds(500));
}

void thread2()
{
    scoped_lock lock(mtxA, mtxB);

    cout << "Thread 2 acquired both locks." << endl;

    this_thread::sleep_for(chrono::milliseconds(500));
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    cout << "No deadlock occurred." << endl;

    return 0;
}
