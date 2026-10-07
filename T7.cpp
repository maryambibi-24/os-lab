#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> counter{0};

void atomic_worker()
{
    for (int i = 0; i < 100000; i++)
    {
        counter.fetch_add(1, memory_order_relaxed);
    }
}

int main()
{
    thread t1(atomic_worker);
    thread t2(atomic_worker);

    t1.join();
    t2.join();

    cout << "Expected value: 200000" << endl;
    cout << "Actual value: " << counter.load() << endl;

    return 0;
}
