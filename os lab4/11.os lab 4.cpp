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
    {
        lock_guard<mutex> lock(mtx);

        q.push(100);

        cout << "Producer added item: 100" << endl;
    }

    cv.notify_one();
}

void consumer()
{
    unique_lock<mutex> lock(mtx);

    cv.wait(lock, [] {
        return !q.empty();
    });

    int item = q.front();
    q.pop();

    cout << "Consumer received item: "
         << item << endl;
}

int main()
{
    thread t1(consumer);
    thread t2(producer);

    t1.join();
    t2.join();

    cout << "Program finished." << endl;

    return 0;
}