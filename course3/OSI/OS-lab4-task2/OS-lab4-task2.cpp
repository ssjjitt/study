#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std; 

void OS04_02_T1() {
    DWORD processID = GetCurrentProcessId();
    for (int i = 0; i < 50; ++i) {
        cout << "OS04_02_T1\tID process: " << processID
            << "\tID thread: " << GetCurrentThreadId() << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void OS04_02_T2() {
    DWORD processID = GetCurrentProcessId();
    for (int i = 0; i < 125; ++i) {
        cout << "OS04_02_T2\tID process: " << processID
            << "\tID thread: " << GetCurrentThreadId() << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    DWORD processID = GetCurrentProcessId();

    thread thread1(OS04_02_T1);
    thread thread2(OS04_02_T2);

    for (int i = 0; i < 100; ++i) {
        cout << "\nMain\tID process: " << processID << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    thread1.join();
    thread2.join();

    return 0;
}