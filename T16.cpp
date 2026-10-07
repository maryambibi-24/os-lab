#include <iostream>
#include <future>
#include <chrono>
using namespace std;

int heavy_calc(int number)
{
    cout << "Heavy computation started..." << endl;

    this_thread::sleep_for(chrono::seconds(2));

    return number * number;
}

int main()
{
    future<int> fut =
        async(launch::async, heavy_calc, 10);

    cout << "Main thread continues doing other work..." << endl;

    int result = fut.get();

    cout << "Final result = "
         << result << endl;

    return 0;
}
