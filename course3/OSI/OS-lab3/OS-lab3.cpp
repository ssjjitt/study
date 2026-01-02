#include <iostream>
#include <windows.h>
/*
длинный цикл с временной задержкой
и с выводом на консоль идентификатора процесса
*/
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    DWORD processID = GetCurrentProcessId();
    while (true) {
        cout << "OS03_01: " << processID << endl;
        Sleep(2000);
    }
}