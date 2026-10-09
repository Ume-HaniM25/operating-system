#include <iostream>
#include <thread>
#include <future>

using namespace std;

int heavy_calc(int number)
{
    return number * number;
}

int main()
{
    future<int> fut = async(launch::async, heavy_calc, 10);

    cout << "Main thread is doing other work..." << endl;

    int result = fut.get();

    cout << "Calculation result: "
         << result << endl;

    return 0;
}