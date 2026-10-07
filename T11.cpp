#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

queue<int> q;
mutex mtx;
condition_variable cv;

void producer()
{
    for (int i = 1; i <= 5; i++)
    {
        {
            lock_guard<mutex> lock(mtx);

            q.push(i);

            cout << "Produced: " << i << endl;
        }

        cv.notify_one();
    }
}

void consumer()
{
    for (int i = 1; i <= 5; i++)
    {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [] {
            return !q.empty();
        });

        int item = q.front();
        q.pop();

        cout << "Consumed: " << item << endl;
    }
}

int main()
{
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
