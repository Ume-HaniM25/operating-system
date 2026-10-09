#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtxA;
mutex mtxB;

void thread1()
{
    lock(mtxA, mtxB);

    lock_guard<mutex> lockA(mtxA, adopt_lock);
    lock_guard<mutex> lockB(mtxB, adopt_lock);

    cout << "Thread 1 acquired both locks." << endl;
}

void thread2()
{
    lock(mtxA, mtxB);

    lock_guard<mutex> lockA(mtxA, adopt_lock);
    lock_guard<mutex> lockB(mtxB, adopt_lock);

    cout << "Thread 2 acquired both locks." << endl;
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    cout << "Program finished without deadlock." << endl;

    return 0;
}