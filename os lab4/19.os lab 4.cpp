#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

bool stop_requested = false;

void worker()
{
    int count = 1;

    while (!stop_requested)
    {
        cout << "Worker is doing work: "
             << count << endl;

        count++;

        this_thread::sleep_for(
            chrono::milliseconds(500)
        );
    }

    cout << "Worker received stop request." << endl;
    cout << "Worker cleaning up resources." << endl;
}

int main()
{
    thread t(worker);

    this_thread::sleep_for(
        chrono::seconds(3)
    );

    stop_requested = true;

    cout << "Main thread requested stop." << endl;

    t.join();

    cout << "Program finished." << endl;

    return 0;
}