#include <iostream>
#include <thread>
#include <functional>

using namespace std;

void worker(int val, int &ref_val)
{
    val = val + 10;
    ref_val = ref_val + 10;

    cout << "Inside thread:" << endl;
    cout << "Value = " << val << endl;
    cout << "Reference = " << ref_val << endl;
}

int main()
{
    int x = 5;
    int y = 10;

    thread t(worker, x, ref(y));

    t.join();

    cout << "After thread:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    return 0;
}