#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;

int permits = 3;

void task(int id)
{
    {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [] {
            return permits > 0;
        });

        permits--;

        cout << "Task " << id
             << " started." << endl;
    }

    this_thread::sleep_for(chrono::seconds(1));

    {
        lock_guard<mutex> lock(mtx);

        permits++;

        cout << "Task " << id
             << " finished." << endl;
    }

    cv.notify_one();
}

int main()
{
    vector<thread> threads;

    for (int i = 1; i <= 6; i++)
    {
        threads.push_back(thread(task, i));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    cout << "All tasks completed." << endl;

    return 0;
}