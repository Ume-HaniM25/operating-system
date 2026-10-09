#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
int data = 100;

void reader(int id)
{
    mtx.lock();

    cout << "Reader " << id
         << " reads data: " << data << endl;

    mtx.unlock();
}

void writer()
{
    mtx.lock();

    data = 200;

    cout << "Writer changed data to: "
         << data << endl;

    mtx.unlock();
}

int main()
{
    thread r1(reader, 1);
    thread r2(reader, 2);

    r1.join();
    r2.join();

    thread w(writer);

    w.join();

    return 0;
}