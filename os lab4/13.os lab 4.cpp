#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;

int arrived = 0;
const int TOTAL_THREADS = 3;

void worker(int id)
{
    cout << "Thread " << id << " completed Phase 1." << endl;

    unique_lock<mutex> lock(mtx);

    arrived++;

    if (arrived == TOTAL_THREADS)
    {
        cv.notify_all();
    }
    else
    {
        cv.wait(lock, [] {
            return arrived == TOTAL_THREADS;
        });
    }

    lock.unlock();

    cout << "Thread " << id << " started Phase 2." << endl;
}

int main()
{
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    t1.join();
    t2.join();
    t3.join();

    cout << "All threads completed." << endl;

    return 0;
}