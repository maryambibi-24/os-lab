#include <iostream>
#include <thread>
#include <functional>
using namespace std;

void worker(int val, int& ref_val)
{
    val = val + 10;
    ref_val = ref_val + 10;

    cout << "Inside thread:" << endl;
    cout << "Value copy = " << val << endl;
    cout << "Reference value = " << ref_val << endl;
}

int main()
{
    int local_x = 20;
    int local_y = 30;

    thread t(worker, local_x, ref(local_y));

    t.join();

    cout << "\nAfter thread:" << endl;
    cout << "local_x = " << local_x << endl;
    cout << "local_y = " << local_y << endl;

    return 0;
}
