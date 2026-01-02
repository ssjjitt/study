#include <iostream>
#include <Windows.h>

int main() {

    setlocale(LC_ALL, "rus");

    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    BOOL bRes = CreateProcessW(L"D:\\univer\\!ОС\\OS-lab7\\x64\\Debug\\OS_07_04_1.exe",
        NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1);

    if (!bRes) {
        printf("error %d\n", GetLastError());
    }

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    BOOL bRes1 = CreateProcessW(L"D:\\univer\\!ОС\\OS-lab7\\x64\\Debug\\OS07_04_2.exe",
        NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2);

    if (!bRes1) {
        printf("error %d\n", GetLastError());
    }


    WaitForSingleObject(pi2.hProcess, INFINITE);
    WaitForSingleObject(pi1.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);



}