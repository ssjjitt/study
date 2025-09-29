#include <iostream>
#include <windows.h>
int main()
{
    const auto application_name_1 = L"OS-lab3-task2-1.exe";
    const auto application_name_2 = L"OS-lab3-task2-2.exe";

    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;
    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);

    if (CreateProcess(application_name_1, nullptr, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si1,
        &pi1))
        std::cout << "Process OS-lab3-task2-1 created\n";
    else
        std::cout << "Process OS-lab3-task2-1 not created\n";

    if (CreateProcess(application_name_2, nullptr, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si2,
        &pi2))
        std::cout << "Process OS-lab3-task2-2 created\n";
    else
        std::cout << "Process OS-lab3-task2-2 not created\n";

    const auto process_id = GetCurrentProcessId();

    for (int i = 0; i < 100; i++)
    {
        std::cout << process_id << std::endl;
        Sleep(1000);
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
}
