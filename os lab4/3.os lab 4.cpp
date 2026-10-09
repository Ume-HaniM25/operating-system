#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void logger()
{
    cout << "Logger thread is running." << endl;

    this_thread::sleep_for(chrono::seconds(2));

    cout << "Logger thread finished." << endl;
}

int main()
{
    thread t(logger);

    t.detach();

    cout << "Main thread continues." << endl;

    this_thread::sleep_for(chrono::seconds(3));

    return 0;
}