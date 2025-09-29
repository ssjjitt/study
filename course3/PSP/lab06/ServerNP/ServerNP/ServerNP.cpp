#include <iostream>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)
using namespace std;


#define INADDR_ANY        (u_long)0x00000000 //любой адрес       +++ 
#define INADDR_LOOPBACK    0x7f000001        // внутренняя петля +++
#define INADDR_BROADCAST  (u_long)0xffffffff // широковещание    +++  
#define INADDR_NONE        0xffffffff        // нет адреса  
#define ADDR_ANY           INADDR_ANY        // любой адрес       

typedef struct sockaddr_in SOCKADDR_IN;    //                     +++
typedef struct sockaddr_in* PSOCKADDR_IN;
typedef struct sockaddr_in FAR* LPSOCKADDR_IN;

string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "Работа функции прервана"; break;
	case WSAEACCES:	msgText = "Разрешение отвергнуто"; break;
	case WSAEFAULT: msgText = "Ошибочный адрес"; break;
	case WSAEINVAL:	msgText = "Ошибка в аргументе";	break;
	case WSAEMFILE:	msgText = "Открыто слишком много файлов"; break;
	case WSAEWOULDBLOCK: msgText = "Ресурс временно недоступен"; break;
	case WSAEINPROGRESS: msgText = "Операция в процессе развития"; break;
	case WSAEALREADY: msgText = "Операция уже выполняется";	break;
	case WSAENOTSOCK: msgText = "Сокет задан неправильно"; break;
	case WSAEDESTADDRREQ: msgText = "Требуется адрес расположения"; break;
	case WSAEMSGSIZE: msgText = "Сообщение слишком длинное"; break;
	case WSAEPROTOTYPE: msgText = "Неправильный тип протокола для сокета"; break;
	case WSAENOPROTOOPT: msgText = "Ошибка в опции протокола"; break;
	case WSAEPROTONOSUPPORT: msgText = "Протокол не поддерживается"; break;
	case WSAESOCKTNOSUPPORT: msgText = "Тип сокета не поддерживается"; break;
	case WSAEOPNOTSUPP: msgText = "Операция не поддерживается"; break;
	case WSAEPFNOSUPPORT: msgText = "Тип протоколов не поддерживается"; break;
	case WSAEAFNOSUPPORT: msgText = "Тип адресов не поддерживается протоколом"; break;
	case WSAEADDRINUSE: msgText = "Адрес уже используется"; break;
	case WSAEADDRNOTAVAIL: msgText = "Запрошенный адрес не может быть использован"; break;
	case WSAENETDOWN: msgText = "Сеть отключена"; break;
	case WSAENETUNREACH: msgText = "Сеть не достижима"; break;
	case WSAENETRESET: msgText = "Сеть разорвала соединение"; break;
	case WSAECONNABORTED: msgText = "Программный отказ связи"; break;
	case WSAECONNRESET: msgText = "Связь не восстановлена"; break;
	case WSAENOBUFS: msgText = "Не хватает памяти для буферов"; break;
	case WSAEISCONN: msgText = "Сокет уже подключен"; break;
	case WSAENOTCONN: msgText = "Сокет не подключен"; break;
	case WSAESHUTDOWN: msgText = "Нельзя выполнить send: сокет завершил работу"; break;
	case WSAETIMEDOUT: msgText = "Закончился отведенный интервал времени"; break;
	case WSAECONNREFUSED: msgText = "Соединение отклонено"; break;
	case WSAEHOSTDOWN: msgText = "Хост в неработоспособном состоянии"; break;
	case WSAEHOSTUNREACH: msgText = "Нет маршрута для хоста"; break;
	case WSAEPROCLIM: msgText = "Слишком много процессов"; break;
	case WSASYSNOTREADY: msgText = "Сеть не доступна"; break;
	case WSAVERNOTSUPPORTED: msgText = "Данная версия недоступна"; break;
	case WSANOTINITIALISED: msgText = "Не выполнена инициализация WS2_32.dll"; break;
	case WSAEDISCON: msgText = "Выполняется отключение"; break;
	case WSATYPE_NOT_FOUND: msgText = "Класс не найден"; break;
	case WSAHOST_NOT_FOUND: msgText = "Хост не найден"; break;
	case WSATRY_AGAIN: msgText = "Неавторизованный хост не найден"; break;
	case WSANO_RECOVERY: msgText = "Неопределенная ошибка"; break;
	case WSANO_DATA: msgText = "Нет записи запрошенного типа"; break;
	case WSASYSCALLFAILURE: msgText = "Аварийное завершение системного вызова"; break;
	case 2: msgText = "Неудачное завершение"; break;
	case ERROR_INVALID_PARAMETER: msgText = "Значение параметра pimax превосходит величину  PIPE_UNLMITED_INSTANCES"; break;
	case ERROR_NO_DATA: msgText = "The pipe is being closed"; break;
	case ERROR_PIPE_CONNECTED: msgText = "There is a process on other end of the pipe"; break;
	case ERROR_PIPE_LISTENING: msgText = "Waiting for a process to open the other end of the pipe"; break;
	case ERROR_CALL_NOT_IMPLEMENTED: msgText = "This function is not supported on this system"; break;
	default: msgText = "**ERROR**"; break;
	}
	return msgText;
};
string SetPipeError(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}



int main()
{
	setlocale(LC_ALL, "Russian");
	HANDLE hPipe;

	LPCSTR pipeName = "\\\\.\\pipe\\Tube";
	//LPCSTR pipeName = "\\\\DESKTOP-9MC22NJ\\pipe\\Tube";

	try {
		hPipe = CreateNamedPipeA(
			pipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_WAIT,
			1, 
			NULL, 
			NULL,
			INFINITE, 
			NULL
		);

		//hPipe = CreateNamedPipeA(
		//	pipeName,                      // Имя канала, включающее имя компьютера
		//	PIPE_ACCESS_DUPLEX,            // Двусторонняя передача данных
		//	PIPE_TYPE_MESSAGE |            // Сообщения
		//	PIPE_READMODE_MESSAGE |
		//	PIPE_WAIT,                     // Ожидание клиента
		//	1,                             // Один клиент
		//	512,                           // Размер выходного буфера
		//	512,                           // Размер входного буфера
		//	0,                             // Тайм-аут ожидания (по умолчанию)
		//	NULL                           // Параметры безопасности
		//);


		if (hPipe == INVALID_HANDLE_VALUE)
			throw SetPipeError("create: ", GetLastError());
		else 
			cout << "Pipe created" << endl;

		/*if (!ConnectNamedPipe(hPipe, NULL))
			throw SetPipeError("connect: ", GetLastError());
		else 
			cout << "Client connected" << endl;

		char rbuf[50];
		DWORD rbufl = 0;
		if (!ReadFile(hPipe, rbuf, sizeof(rbuf) - 1, &rbufl, NULL))
			throw SetPipeError("readfile: ", GetLastError());
		else 
			cout << "Message from client: " << rbuf << endl;

		char wbuf[50] = "hello from server";
		DWORD wbufl = 0;
		if (!WriteFile(hPipe, wbuf, sizeof(wbuf) - 1, &wbufl, NULL))
			throw SetPipeError("writefile: ", GetLastError());
		cout << "message sended." << endl;

		DisconnectNamedPipe(hPipe);*/



		char rbuf[50];
		DWORD rbufl = 0;
		DWORD wbufl = 0;
		bool isReading = true;

		while (true) {
			cout << "Waitinig for client..." << endl;

			if (!ConnectNamedPipe(hPipe, NULL))
				throw SetPipeError("connect: ", GetLastError());
			else
				cout << "Client connected" << endl;

			while (true) {
				
				memset(&rbuf, sizeof(rbuf), 0);
				rbufl = 0;

				if (!ReadFile(hPipe, rbuf, sizeof(rbuf), &rbufl, NULL))
					break;
					//throw SetPipeError("readfile: ", GetLastError());

				cout << "Message from client: " << rbuf << endl;

				wbufl = 0;
				if (!WriteFile(hPipe, rbuf, sizeof(rbuf) - 1, &wbufl, NULL))
					throw SetPipeError("writefile: ", GetLastError());
				cout << "message sended." << endl;
			}
			DisconnectNamedPipe(hPipe);
		}

		CloseHandle(hPipe);
	}
	catch (string errorMsgText) {
		cout << endl << "Error: " << errorMsgText;
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);
	}


	return 0;
}


