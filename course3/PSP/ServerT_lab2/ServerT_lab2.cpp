#include <iostream>
#include <clocale>
#include <ctime>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable:4996)
using namespace std;

string  GetErrorMsgText(int code)    // cформировать текст ошибки 
{
	string msgText;
	switch (code)                      // проверка кода возврата  
	{
	case WSAEINTR: msgText = "WSAEINTR: Работа функции прервана ";         break;
	case WSAEACCES: msgText = "WSAEACCES: Разрешение отвергнуто";        break;
	case WSAEFAULT: msgText = "WSAEFAULT: Ошибочный адрес"; break;
	case WSAEINVAL: msgText = "WSAEINVAL: Ошибка в аргументе"; break;
	case WSAEMFILE: msgText = "WSAEMFILE: Слишком много файлов открыто"; break;
	case WSAEWOULDBLOCK:msgText = "WSAEWOULDBLOCK: Ресурс временно недоступен"; break;
	case WSAEINPROGRESS:msgText = "WSAEINPROGRESS: Операция в процессе развития"; break;
	case WSAEALREADY:msgText = "WSAEALREADY: Операция уже выполняется "; break;
	case WSAENOTSOCK:msgText = "WSAENOCTSOCK: Сокет задан неправильно   "; break;
	case WSAEDESTADDRREQ:msgText = "WSAEDESTADDRREQ: Требуется адрес расположения "; break;
	case WSAEMSGSIZE:msgText = "WSAEMSGSIZE: Сообщение слишком длинное "; break;
	case WSAEPROTOTYPE:msgText = "WSAEPROTOTYPE: Неправильный тип протокола для сокета "; break;
	case WSAENOPROTOOPT:msgText = "WSAENOPROTOOPT: Ошибка в опции протокола"; break;
	case WSAEPROTONOSUPPORT:msgText = "WSAEPROTONOSUPPORT: Протокол не поддерживается "; break;
	case WSAESOCKTNOSUPPORT:msgText = "WSAESOCKTNOSUPPORT: Тип сокета не поддерживается "; break;
	case WSAEOPNOTSUPP:msgText = "WSAEOPNOTSUPP: Операция не поддерживается "; break;
	case WSAEPFNOSUPPORT:msgText = "WSAEPFNOSUPPORT: Тип протоколов не поддерживается "; break;
	case WSAEAFNOSUPPORT:msgText = "WSAEAFNOSUPPORT: Тип адресов не поддерживается протоколом"; break;
	case WSAEADDRINUSE:msgText = "WSAEADDRINUSE: Адрес уже используется "; break;
	case WSAEADDRNOTAVAIL:msgText = "WSAEADDRNOTAVAIL: Запрошенный адрес не может быть использован"; break;
	case WSAENETDOWN:msgText = "WSAENETDOWN: Сеть отключена "; break;
	case WSAENETUNREACH:msgText = "WSAENETUNREACH: Сеть не достижима"; break;
	case WSAENETRESET:msgText = "WSAENETRESET: Сеть разорвала соединение"; break;
	case WSAECONNABORTED:msgText = "WSAECONNABORTED: Программный отказ связи "; break;
	case WSAECONNRESET:msgText = "WSAECONNRESET: Связь восстановлена "; break;
	case WSAENOBUFS:msgText = "WSAENOBUFS: Не хватает памяти для буферов"; break;
	case WSAEISCONN:msgText = "WSAEISCONN: Сокет уже подключен"; break;
	case WSAENOTCONN:msgText = "WSAENOTCONN: Сокет не подключен"; break;
	case WSAESHUTDOWN:msgText = "WSAESHUTDOWN: Нельзя выполнить send: сокет завершил работу"; break;
	case WSAETIMEDOUT:msgText = "WSAETIMEDOUT: Закончился отведенный интервал  времени"; break;
	case WSAECONNREFUSED:msgText = "WSAECONNREFUSED: Соединение отклонено"; break;
	case WSAEHOSTDOWN:msgText = "WSAEHOSTDOWN: Хост в неработоспособном состоянии"; break;
	case WSAEHOSTUNREACH:msgText = "WSAEHOSTUNREACH: Нет маршрута для хоста"; break;
	case WSAEPROCLIM:msgText = "WSAEPROCLIM: Слишком много процессов "; break;
	case WSASYSNOTREADY:msgText = "WSASYSNOTREADY: Сеть не доступна "; break;
	case WSAVERNOTSUPPORTED:msgText = "WSAVERNOTSUPPORTED: Данная версия недоступна"; break;
	case WSANOTINITIALISED:msgText = "WSANOTINITIALISED: Не выполнена инициализация WS2_32.DLL"; break;
	case WSAEDISCON:msgText = "WSAEDISCON: Выполняется отключение"; break;
	case WSATYPE_NOT_FOUND:msgText = "WSATYPE_NOT_FOUND: Класс не найден"; break;
	case WSAHOST_NOT_FOUND:msgText = "WSAHOST_NOT_FOUND: Хост не найден"; break;
	case WSATRY_AGAIN:msgText = "WSATRY_AGAIN: Неавторизированный хост не найден"; break;
	case WSANO_RECOVERY:msgText = "WSANO_RECOVERY: Неопределенная  ошибка"; break;
	case WSANO_DATA:msgText = "WSANO_DATA: Нет записи запрошенного типа "; break;
	case WSA_INVALID_HANDLE:msgText = "WSA_INVALID_HANDLE: Указанный дескриптор события  с ошибкой"; break;
	case WSA_INVALID_PARAMETER:msgText = "WSA_INVALID_PARAMETER: Один или более параметров с ошибкой"; break;
	case WSA_IO_INCOMPLETE:msgText = "WSA_IO_INCOMPLETE: Объект ввода-вывода не в сигнальном состоянии"; break;
	case WSA_IO_PENDING:msgText = "WSA_IO_PENDING: Операция завершится позже"; break;
	case WSA_NOT_ENOUGH_MEMORY:msgText = "WSA_NOT_ENOUGH_MEMORY: Не достаточно памяти"; break;
	case WSA_OPERATION_ABORTED:msgText = "WSA_OPERATION_ABORTED: Операция отвергнута"; break;
	case WSAEINVALIDPROCTABLE:msgText = "WSAEINVALIDPROCTABLE: Ошибочный сервис"; break;
	case WSAEINVALIDPROVIDER:msgText = "WSAEINVALIDPROVIDER: Ошибка в версии сервиса"; break;
	case WSAEPROVIDERFAILEDINIT:msgText = "WSAEPROVIDERFAILEDINIT: Невозможно инициализировать сервис"; break;
	case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE: Аварийное завершение системного вызова"; break;
	default:                msgText = "***ERROR***";      break;
	};
	return msgText;
};

string SetErrorMsgText(string msgText, int code) //функция для обр-ки стандартных ошибок
{
	return  msgText + GetErrorMsgText(code);
};

int main()
{
	SOCKET  sS;	// дескриптор сокета  
	WSADATA wsaData; // структура для хранения инфы

	try
	{
		// ИНИЦИАЛИЗАЦИЯ БИБЛИОТЕКИ WINSOCK 
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());
		// СОЗДАНИЕ СОКЕТА
		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("socket:", WSAGetLastError()); 
		// ПАРАМЕТРЫ  СОКЕТА SS
		SOCKADDR_IN serv; // структура для хранения параметров
		serv.sin_family = AF_INET; // используется IP-адресация (IPv4) 
		serv.sin_port = htons(2000); // порт 2000
		serv.sin_addr.s_addr = INADDR_ANY; // любой собственный IP-адрес
		// ПРИВЯЗКА СОКЕТА К АДРЕСУ И ПОРТУ
		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) //установка параметров сокета
			throw  SetErrorMsgText("bind:", WSAGetLastError());
		// ПРОСЛУШИВАНИЕ ВХОДЯЩИХ ПОДКЛЮЧЕНИЙ
		if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
			throw  SetErrorMsgText("listen:", WSAGetLastError());

		int i = 0;
		WSADATA ws;
		SOCKET s;
		SOCKET c;
		char ibuf[50];
		char obuf[50] = "Hello from Client";
		int t;

		if (FAILED(WSAStartup(MAKEWORD(1, 1), &ws)))
			cout << "socket:" << WSAGetLastError() << endl;
		if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, 0)))
			cout << "socket:" << WSAGetLastError() << endl;

		sockaddr_in c_adr;
		sockaddr_in s_adr;
		{
			s_adr.sin_port = htons(2000);
			s_adr.sin_addr.S_un.S_addr = inet_addr("172.20.10.2");
			s_adr.sin_family = AF_INET;
		}

		if (SOCKET_ERROR == (bind(s, (LPSOCKADDR)&s_adr, sizeof(s_adr))))
			cout << "bind:" << WSAGetLastError() << endl;

		if (SOCKET_ERROR == listen(s, 2))
			cout << "listen:" << WSAGetLastError << endl;

		// ОБРАБОТКА ВХОДЯЩИХ
		while (true)
		{
			int lcInt = sizeof(c_adr);
			if (INVALID_SOCKET == (c = accept(s, (sockaddr*)&c_adr, &lcInt))) 
				// БЛОКИРУЕТ ВЫПОЛНЕНИЕ, ПОКА НЕ ПОСТУПИТ ВХОДЯЩЕЕ | ЕСЛИ УСПЕШНО, ТО ВЫВОД ИНФЫ
				cout << "accept:" << WSAGetLastError() << endl;

			cout << "Client connected." << endl;
			cout << "Client IP:    " << inet_ntoa(c_adr.sin_addr) << endl;
			cout << "Client port:  " << htons(c_adr.sin_port) << "\n\n";

			int time = clock();
			// ОБМЕН ДАННЫМИ С КЛИЕНТОМ
			while (true)
			{
				// ПОЛУЧАЕТ ДАННЫЕ ОТ КЛИЕНТА | ЕСЛИ КЛИЕНТ ОТПРАВЛЯЕТ "CLOSE", СОЕДИНЕНИЕ РАЗРЫВАЕТСЯ
				if (SOCKET_ERROR == recv(c, ibuf, sizeof(ibuf), NULL))
					break;

				cout << ibuf << " " << i << "\n";
				i++;

				if (!strcmp(ibuf, "CLOSE")) { break; }
				// ОТПРАВЛЯЕТ ДАННЫЕ ОБРАТНО КЛИЕНТУ
				if (SOCKET_ERROR == send(c, obuf, strlen(obuf) + 1, NULL))
					break;
			}
			i = 0;
			cout << "Client Disconected.\n";
			cout << "Program was running for " << time << " ticks or " << ((float)time) / CLOCKS_PER_SEC << " seconds.\n\n";
		}

		// ЗАКРЫТИЕ СОКЕТОВ И ЗАВЕРШЕНИЕ РАБОТЫ
		if (closesocket(c) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket:", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());

		if (closesocket(sS) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR) //завершение работы с библиотекой
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());

	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError: " << errorMsgText;
	}

	//................................................................
	return 0;

}
