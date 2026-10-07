#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex mtx;

void safe_increment()
{
    for (int i = 0; i < 100000; i++)
    {
        lock_guard<mutex> lock(mtx);

        counter++;
    }
}

int main()
{
    thread t1(safe_increment);
    thread t2(safe_increment);

    t1.join();
    t2.join();

    cout << "Expected value: 200000" << endl;
    cout << "Actual value: " << counter << endl;

    return 0;
}
