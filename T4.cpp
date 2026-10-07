#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void worker()
{
    for (int i = 1; i <= 5; i++)
    {
        cout << "Worker running..." << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main()
{
    {
        jthread jt(worker);

        cout << "jthread created." << endl;
    }

    cout << "jthread automatically joined." << endl;

    return 0;
}
