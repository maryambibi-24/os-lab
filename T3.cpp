#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void logger()
{
    for (int i = 1; i <= 5; i++)
    {
        cout << "Logger: flushing buffer to disk..." << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "Logger thread finished." << endl;
}

int main()
{
    thread t(logger);

    t.detach();

    cout << "Main thread continues independently." << endl;

    this_thread::sleep_for(chrono::seconds(6));

    return 0;
}
