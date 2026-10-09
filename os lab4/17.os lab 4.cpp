#include <iostream>
#include <thread>

using namespace std;

thread_local int txn_id = 0;

void run(int id)
{
    txn_id++;

    cout << "Thread " << id
         << " transaction ID = "
         << txn_id << endl;
}

int main()
{
    thread t1(run, 1);
    thread t2(run, 2);
    thread t3(run, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}