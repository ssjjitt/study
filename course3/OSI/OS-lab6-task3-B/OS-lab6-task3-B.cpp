#include <iostream>
#include <Windows.h>

int main()
{
	int pid = GetCurrentProcessId();
	HANDLE mutex = OpenMutex(SYNCHRONIZE, FALSE, L"OS-lab6-task3");

	for (int i = 1; i <= 90; ++i)
	{
		if (i == 30)
			WaitForSingleObject(mutex, INFINITE);

		else if (i == 60)
			ReleaseMutex(mutex);

		printf("6-3-B %d. PID = %d\n", i, pid);
		Sleep(100);
	}

	CloseHandle(mutex);


	system("pause");
	return 0;
}