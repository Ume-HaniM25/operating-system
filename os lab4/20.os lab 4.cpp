#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int N = 5;

mutex forks[N];

void dine(int philosopher_id)
{
    int left = philosopher_id;
    int right = (philosopher_id + 1) % N;

    int first = min(left, right);
    int second = max(left, right);

    cout << "Philosopher " << philosopher_id
         << " is waiting for forks." << endl;

    unique_lock<mutex> lock1(forks[first]);
    unique_lock<mutex> lock2(forks[second]);

    cout << "Philosopher " << philosopher_id
         << " is eating." << endl;

    this_thread::sleep_for(
        chrono::milliseconds(500)
    );

    cout << "Philosopher " << philosopher_id
         << " finished eating." << endl;
}

int main()
{
    thread philosophers[N];

    for (int i = 0; i < N; i++)
    {
        philosophers[i] = thread(dine, i);
    }

    for (int i = 0; i < N; i++)
    {
        philosophers[i].join();
    }

    cout << "All philosophers finished." << endl;

    return 0;
}