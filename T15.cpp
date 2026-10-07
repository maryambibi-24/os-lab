#include <iostream>
#include <thread>
#include <future>
using namespace std;

void worker(promise<int> prom)
{
    int data = 42;

    cout << "Worker calculated: " << data << endl;

    prom.set_value(data);
}

int main()
{
    promise<int> prom;

    future<int> fut = prom.get_future();

    thread t(worker, move(prom));

    int result = fut.get();

    cout << "Main thread received: "
         << result << endl;

    t.join();

    return 0;
}
