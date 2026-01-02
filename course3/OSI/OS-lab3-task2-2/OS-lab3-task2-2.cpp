#include <iostream>
#include <windows.h>

int main() {
    setlocale(LC_ALL, "rus");
    DWORD processID = GetCurrentProcessId();

    for (int i = 0; i < 125; ++i) {
        std::cout << "OS-lab3-task2-2: " << processID << std::endl;
        Sleep(1000);  
    }

    return 0;
}