#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void worker(stop_token stoken)
{
    while (!stoken.stop_requested())
    {
        cout << "Worker is doing work..." << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "Stop requested." << endl;
    cout << "Worker cleaning up resources..." << endl;
}

int main()
{
    jthread my_jthread(worker);

    this_thread::sleep_for(chrono::seconds(3));

    cout << "Main thread requesting stop..." << endl;

    my_jthread.request_stop();

    return 0;
}
