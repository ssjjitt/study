#include <Windows.h>
#include <bitset>
#include <iostream>
using namespace std;

void main() {
    setlocale(LC_ALL, "rus");

    DWORD processID = GetCurrentProcessId();
    cout << "Идентификатор текущего процесса: " << processID << endl;

    DWORD threadID = GetCurrentThreadId();
    cout << "Идентификатор текущего (main) потока: " << threadID << endl;

    HANDLE hProcess = GetCurrentProcess();

    DWORD priorityClass = GetPriorityClass(hProcess);
    string processPriorityClassName;

    switch (priorityClass) {
    case REALTIME_PRIORITY_CLASS:
        processPriorityClassName = "Realtime";
        break;
    case HIGH_PRIORITY_CLASS:
        processPriorityClassName = "High";
        break;
    case ABOVE_NORMAL_PRIORITY_CLASS:
        processPriorityClassName = "Above Normal";
        break;
    case NORMAL_PRIORITY_CLASS:
        processPriorityClassName = "Normal";
        break;
    case BELOW_NORMAL_PRIORITY_CLASS:
        processPriorityClassName = "Below Normal";
        break;
    case IDLE_PRIORITY_CLASS:
        processPriorityClassName = "Idle";
        break;
    default:
        processPriorityClassName = "Unknown";
    }
    cout << "Приоритет (приоритетный класс) текущего процесса: " << priorityClass << " - " << processPriorityClassName << endl;

    HANDLE hThread = GetCurrentThread();
    int threadPriority = GetThreadPriority(hThread);
    cout << "Приоритет текущего потока: " << threadPriority << endl;

    DWORD_PTR processAffinityMask;
    DWORD_PTR systemAffinityMask;
    GetProcessAffinityMask(GetCurrentProcess(), &processAffinityMask, &systemAffinityMask);

    cout << "Маска (affinity mask) доступных процессу процессоров в двоичном виде: " << bitset<sizeof(DWORD_PTR) * 8>(processAffinityMask) << endl;

    int numProcessors = 0;
    for (int i = 0; i < sizeof(DWORD_PTR) * 8; i++) {
        if ((processAffinityMask >> i) & 1) {
            numProcessors++;
        }
    }

    cout << "Количество процессоров, доступных процессу: " << numProcessors << endl;

    DWORD currentProcessor = GetCurrentProcessorNumber();

    cout << "Процессор, назначенный текущему потоку: " << currentProcessor << endl;

    CloseHandle(hThread);

}