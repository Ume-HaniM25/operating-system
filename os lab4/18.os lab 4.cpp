#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

using namespace std;

queue<function<void()> > tasks;

mutex queue_mtx;
condition_variable cv;

bool stop = false;

void worker(int id)
{
    while (true)
    {
        function<void()> task;

        {
            unique_lock<mutex> lock(queue_mtx);

            cv.wait(lock, [] {
                return stop || !tasks.empty();
            });

            if (stop && tasks.empty())
                return;

            task = tasks.front();
            tasks.pop();
        }

        cout << "Worker " << id << " executing task." << endl;

        task();
    }
}

void work(int number)
{
    cout << "Task " << number << " is completed." << endl;
}

int main()
{
    thread t1(worker, 1);
    thread t2(worker, 2);

    {
        lock_guard<mutex> lock(queue_mtx);

        for (int i = 1; i <= 4; i++)
        {
            tasks.push([i]() {
                work(i);
            });
        }
    }

    cv.notify_all();

    this_thread::sleep_for(chrono::seconds(1));

    {
        lock_guard<mutex> lock(queue_mtx);
        stop = true;
    }

    cv.notify_all();

    t1.join();
    t2.join();

    cout << "All tasks completed." << endl;

    return 0;
}