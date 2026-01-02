#include <iostream>
#include <Windows.h>

using namespace std;


PROCESS_INFORMATION createProcess(LPCWSTR path)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	if (CreateProcessW(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		cout << "Process created\n";
	else
		cout << "Error CreateProcessW\n";

	return pi;
}


int main()
{
	int pid = GetCurrentProcessId();
	const int size = 2;
	HANDLE semaphore;
	HANDLE processes[size];

	processes[0] = createProcess(L"D:\\univer\\!ОС\\OS-lab6\\x64\\Debug\\OS-lab6-task4-A.exe").hProcess;
	processes[1] = createProcess(L"D:\\univer\\!ОС\\OS-lab6\\x64\\Debug\\OS-lab6-task4-B.exe").hProcess;

	semaphore = CreateSemaphore(NULL, 2, 2, L"OS-lab6-task4");

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
			WaitForSingleObject(semaphore, INFINITE);

		else if (i == 60)
			ReleaseSemaphore(semaphore, 1, NULL);

		printf("6-4 %d. PID = %d\n", i, pid);
		Sleep(100);
	}

	WaitForMultipleObjects(size, processes, TRUE, INFINITE);
	for (int i = 0; i < size; i++)
		CloseHandle(processes[i]);

	CloseHandle(semaphore);
	system("pause");
	return 0;
}