#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

const int NUM_PHILOSOPHERS = 5;

vector<mutex> forks(NUM_PHILOSOPHERS);

void dine(int philosopher_id)
{
    int left_id = philosopher_id;
    int right_id = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    int first = min(left_id, right_id);
    int second = max(left_id, right_id);

    {
        unique_lock<mutex> l1(forks[first]);

        cout << "Philosopher "
             << philosopher_id
             << " picked fork "
             << first << endl;

        unique_lock<mutex> l2(forks[second]);

        cout << "Philosopher "
             << philosopher_id
             << " picked fork "
             << second << endl;

        cout << "Philosopher "
             << philosopher_id
             << " is eating." << endl;

        this_thread::sleep_for(chrono::milliseconds(500));

        cout << "Philosopher "
             << philosopher_id
             << " finished eating." << endl;
    }
}

int main()
{
    vector<thread> philosophers;

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosophers.emplace_back(dine, i);
    }

    for (auto& t : philosophers)
    {
        t.join();
    }

    cout << "All philosophers finished." << endl;

    return 0;
}
