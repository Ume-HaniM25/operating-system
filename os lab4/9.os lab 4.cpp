#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtxA;
mutex mtxB;

void thread1()
{
    lock_guard<mutex> lockA(mtxA);

    cout << "Thread 1 locked A" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> lockB(mtxB);

    cout << "Thread 1 locked B" << endl;
}

void thread2()
{
    lock_guard<mutex> lockB(mtxB);

    cout << "Thread 2 locked B" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> lockA(mtxA);

    cout << "Thread 2 locked A" << endl;
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    cout << "Program finished." << endl;

    return 0;
}