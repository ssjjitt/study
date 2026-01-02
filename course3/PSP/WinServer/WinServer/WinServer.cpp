// WinServer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#define BASE_PATH_PIPE L"\\\\.\\pipe\\"
#define SIZE_BUFFER 2048

#define MESSAGE L"Message"
#define SIZE_MSG_BYTES 16

DWORD WINAPI InstanceThread(_In_ LPVOID hPipe);

int main(int argc, char* params[])
{
	BOOL isConnected = FALSE;
	DWORD dwThreadId = 0;
	HANDLE hPipe = NULL;
	std::wstring namePipe(BASE_PATH_PIPE);
	std::wstring tmp;
	std::list<HANDLE> threads;

	std::cout << "Write name of pipe: " << std::endl;
	std::wcin >> tmp;
	namePipe.append(tmp);

	while (TRUE)
	{
		std::wcout << L"Main thread awake creating pipe with path: " 
			<< namePipe << std::endl;
		std::wcout << L"Wait for client" << std::endl;
		hPipe = CreateNamedPipeW(
			namePipe.c_str(),
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			SIZE_BUFFER,
			SIZE_BUFFER,
			INFINITE,
			NULL);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			std::wcout << L"Error of creating pipe! Process will be terminated!" << std::endl;
			return EXIT_FAILURE;
		}

		isConnected = ConnectNamedPipe(hPipe, NULL);
		if (isConnected)
		{
			std::wcout << L"Client connected. Creating thread for user" << std::endl;
			HANDLE hThread = CreateThread(
				NULL,
				NULL,
				InstanceThread,
				(LPVOID) hPipe,
				NULL,
				&dwThreadId);
			if (hThread == INVALID_HANDLE_VALUE)
				std::wcout << L"Error of making thread!" << std::endl;
			else
			{
				++dwThreadId;
				threads.push_back(hThread);
			}
		}
		else
		{
			std::wcout << L"Error of connection user" << std::endl;
			CloseHandle(hPipe);
		}
	}

	std::for_each(threads.cbegin(), threads.cend(),
		[](HANDLE h)
	{
		CloseHandle(h);
	});
	CloseHandle(hPipe);

    return EXIT_SUCCESS;
}

DWORD WINAPI InstanceThread(_In_ LPVOID hPipe)
{
	LPWSTR strRequest = new WCHAR[SIZE_BUFFER + 1];
	memset(strRequest, 0, (SIZE_BUFFER + 1) * sizeof(WCHAR));
	DWORD cntBytesRead = 0;
	DWORD cntBytesWrited = 0;
	BOOL isSucsses = FALSE;

	HANDLE pipe = (HANDLE)hPipe;
	/*По MSDN тут должны быть 3 проверка. Первая - на то канал равен INVALID_HANDLE_VALUE
	эта проверка уже была в функции main. Зачем здесь - непонятно
	Ещё 2 проверки - на то равны ли строки NULL*/
	std::wcout << L"Instance created, and wait for messages" << std::endl;

	while (TRUE)
	{
		isSucsses = ReadFile(
			pipe,
			strRequest,
			SIZE_BUFFER * sizeof(WCHAR),
			&cntBytesRead,
			NULL);

		if (!isSucsses)
		{
			std::wcout << "Error of read user message or user disconnect" << std::endl;
			break;
		}
		else
			std::wcout << strRequest << std::endl;

		isSucsses = WriteFile(
			pipe,
			MESSAGE,
			SIZE_MSG_BYTES,
			&cntBytesWrited,
			NULL
		);

		if (!isSucsses || cntBytesWrited != SIZE_MSG_BYTES)
		{
			std::wcout << L"Error of reply!" << std::endl;
			break;
		}
		else
			std::wcout << L"Message will be replied" << std::endl;
	}

	if(strRequest)
		delete[] strRequest;
	CloseHandle(pipe);
	ExitThread(0);
}