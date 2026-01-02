#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;

int main() {
    DWORD process = GetCurrentProcessId();
    DWORD thread = GetCurrentThreadId();

    while (true) {
        cout << "ID process: " << process << "\tID thread: " << thread << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}