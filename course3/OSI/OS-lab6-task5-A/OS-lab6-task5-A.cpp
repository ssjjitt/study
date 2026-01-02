#include <iostream>
#include <Windows.h>



int main()
{
	int pid = GetCurrentProcessId();
	HANDLE event = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"OS-lab6-task5");

	WaitForSingleObject(event, INFINITE);
	SetEvent(event);
	for (int i = 1; i <= 90; i++)
	{
		printf("6-5-A %d. PID = %d\n", i, pid);
		Sleep(100);
	}

	CloseHandle(event);
	system("pause");
	return 0;
}