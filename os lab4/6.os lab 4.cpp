#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
int counter = 0;

void safe_increment()
{
    for (int i = 0; i < 100000; i++)
    {
        lock_guard<mutex> lock(mtx);

        counter++;
    }
}

int main()
{
    thread t1(safe_increment);
    thread t2(safe_increment);

    t1.join();
    t2.join();

    cout << "Final counter = " << counter << endl;

    return 0;
}