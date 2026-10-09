#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;

bool ready = false;

void worker(int id)
{
    unique_lock<mutex> lock(mtx);

    cv.wait(lock, [] {
        return ready;
    });

    cout << "Worker " << id << " started." << endl;
}

int main()
{
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);

    cout << "Main thread preparing shared memory..." << endl;

    {
        lock_guard<mutex> lock(mtx);
        ready = true;
    }

    cv.notify_all();

    t1.join();
    t2.join();
    t3.join();

    cout << "All workers released." << endl;

    return 0;
}