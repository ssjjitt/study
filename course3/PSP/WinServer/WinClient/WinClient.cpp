// WinClient.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main(int argc, char* args[])
{
	HANDLE hPipe = NULL;
	DWORD dwMode = 0;
	BOOL isSuccess = FALSE;
	DWORD iCountIO = 0;

	LPWSTR str = new WCHAR[260];
	memset(str, 0, 259 * 2);

	std::wstring server;
	std::wcout << L"Print name of server, or . for localhost" << std::endl;
	std::getline(std::wcin, server);

	std::wstring pipe;
	std::wcout << L"Print name of pipe:" << std::endl;
	std::getline(std::wcin, pipe);

	std::wstring namePipe(L"\\\\");
	namePipe.append(server);
	namePipe.append(L"\\pipe\\");
	namePipe.append(pipe);
	std::wcout << L"Path to pipe: " << namePipe << std::endl;

	std::wstring message;
	std::wcout << L"Write message: " << std::endl;
	std::getline(std::wcin, message);

	//while (true)
	//{
		hPipe = CreateFile(
			namePipe.c_str(),
			GENERIC_ALL,
			0, 
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
			return EXIT_FAILURE;

		WaitNamedPipe(namePipe.c_str(), INFINITE);

		dwMode = PIPE_READMODE_MESSAGE;

		isSuccess = SetNamedPipeHandleState(
			hPipe,
			&dwMode,
			NULL,
			NULL);

		if(!isSuccess)
		{ 
			std::wcout << L"Can't edit mode of pipe!";
			return EXIT_FAILURE;
			//break;
		}

		std::wcout << L"Sending message to server" << std::endl;

		isSuccess = WriteFile
		(
			hPipe,
			message.c_str(),
			(message.size() + 1) * sizeof(wchar_t),
			&iCountIO,
			NULL);

		if (iCountIO != (message.size() + 1) * sizeof(wchar_t) || !isSuccess)
		{
			std::wcout << L"Error of push message to server!" << std::endl;
			return EXIT_FAILURE;
			//break;
		}

		std::wcout << "Message pushed to server" << std::endl;

		do
		{
			isSuccess = ReadFile(
				hPipe,
				str,
				259 * sizeof(WCHAR),
				&iCountIO,
				NULL);

			if (iCountIO > 0 && isSuccess)
				std::wcout << L"Message from server: " << str << std::endl;
			
		}
		while(!isSuccess);
	//}

	CloseHandle(hPipe);
	delete[] str;
	system("pause");
    return EXIT_SUCCESS;
}

