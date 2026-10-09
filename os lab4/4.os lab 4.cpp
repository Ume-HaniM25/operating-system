#include <iostream>
#include <thread>

using namespace std;

void worker_fn()
{
    cout << "Worker thread is running." << endl;
}

int main()
{
    thread t(worker_fn);

    cout << "Main thread is running." << endl;

    // Automatically wait for the thread
    if (t.joinable())
    {
        t.join();
    }

    return 0;
}