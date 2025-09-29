#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <tchar.h>
#include <ctime>
#include <fstream>
#include "Winsock2.h" 
#pragma comment(lib, "WS2_32.lib") 
using namespace std;
string GetErrorMsgText(int code) // cформировать текст ошибки
{
	string msgText;
	switch (code) // проверка кода возврата
	{
	case WSAEINTR: msgText = "WSAEINTR"; break;
	case WSAEACCES: msgText = "WSAEACCES"; break;
	case WSAEFAULT: msgText = "WSAEFAULT"; break;
	case WSAEINVAL: msgText = "WSAEINVAL"; break;
	case WSAEMFILE: msgText = "WSAEMFILE"; break;
	case WSAEWOULDBLOCK: msgText = "WSAEWOULDBLOCK"; break;
	case WSAEINPROGRESS: msgText = "WSAEINPROGRESS"; break;
	case WSAEALREADY: msgText = "WSAEALREADY"; break;
	case WSAENOTSOCK: msgText = "WSAENOTSOCK"; break;
	case WSAEDESTADDRREQ: msgText = "WSAEDESTADDRREQ"; break;
	case WSAEMSGSIZE: msgText = "WSAEMSGSIZE"; break;
	case WSAEPROTOTYPE: msgText = "WSAEPROTOTYPE"; break;
	case WSAENOPROTOOPT: msgText = "WSAENOPROTOOPT"; break;
	case WSAEPROTONOSUPPORT: msgText = "WSAEPROTONOSUPPORT"; break;
	case WSAESOCKTNOSUPPORT: msgText = "WSAESOCKTNOSUPPORT"; break;
	case WSAEOPNOTSUPP: msgText = "WSAEOPNOTSUPP"; break;
	case WSAEPFNOSUPPORT: msgText = "WSAEPFNOSUPPORT"; break;
	case WSAEAFNOSUPPORT: msgText = "WSAEAFNOSUPPORT"; break;
	case WSAEADDRINUSE: msgText = "WSAEADDRINUSE"; break;
	case WSAEADDRNOTAVAIL: msgText = "WSAEADDRNOTAVAIL"; break;
	case WSAENETDOWN: msgText = "WSAENETDOWN"; break;
	case WSAENETUNREACH: msgText = "WSAENETUNREACH"; break;
	case WSAENETRESET: msgText = "WSAENETRESET"; break;
	case WSAECONNABORTED: msgText = "WSAECONNABORTED"; break;
	case WSAECONNRESET: msgText = "WSAECONNRESET"; break;
	case WSAENOBUFS: msgText = "WSAENOBUFS"; break;
	case WSAEISCONN: msgText = "WSAEISCONN"; break;
	case WSAENOTCONN: msgText = "WSAENOTCONN"; break;
	case WSAESHUTDOWN: msgText = "WSAESHUTDOWN"; break;
	case WSAETIMEDOUT: msgText = "WSAETIMEDOUT"; break;
	case WSAECONNREFUSED: msgText = "WSAECONNREFUSED"; break;
	case WSAEHOSTDOWN: msgText = "WSAEHOSTDOWN"; break;
	case WSAEHOSTUNREACH: msgText = "WSAEHOSTUNREACH"; break;
	case WSAEPROCLIM: msgText = "WSAEPROCLIM"; break;
	case WSASYSNOTREADY: msgText = "WSASYSNOTREADY"; break;
	case WSAVERNOTSUPPORTED: msgText = "WSAVERNOTSUPPORTED"; break;
	case WSANOTINITIALISED: msgText = "WSANOTINITIALISED"; break;
	case WSAEDISCON: msgText = "WSAEDISCON"; break;
	case WSATYPE_NOT_FOUND: msgText = "WSATYPE_NOT_FOUND"; break;
	case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND"; break;
	case WSATRY_AGAIN: msgText = "WSATRY_AGAIN"; break;
	case WSANO_RECOVERY: msgText = "WSANO_RECOVERY"; break;
	case WSANO_DATA: msgText = "WSANO_DATA"; break;
	case WSA_INVALID_HANDLE: msgText = "WSA_INVALID_HANDLE"; break;
	case WSA_INVALID_PARAMETER: msgText = "WSA_INVALID_PARAMETER"; break;
	case WSA_IO_INCOMPLETE: msgText = "WSA_IO_INCOMPLETE"; break;
	case WSA_IO_PENDING: msgText = "WSA_IO_PENDING"; break;
	case WSA_NOT_ENOUGH_MEMORY: msgText = "WSA_NOT_ENOUGH_MEMORY"; break;
	case WSA_OPERATION_ABORTED: msgText = "WSA_OPERATION_ABORTED"; break;
		//..........коды WSAGetLastError ..........................
	case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
	default: msgText = "***ERROR***"; break;
	};
	return msgText;
};
string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};
struct CA					//блок управления секцией
{
	char ipaddr[15];		//ip-адрес координатора
	char resurce[20];		//имя ресурса
	int clientnumber;		//номер клиента
	enum Status
	{
		NOINIT,			//начальное состояние
		INIT,			//выполнена инициализация
		ENTER,			//выполнен вход в секцию
		LEAVE,			//выполнен выход из секции
		WAIT			//ожидание входа
	} status;			//состояние
};

string GetStatusText(CA::Status status) {
	switch (status) {
	case CA::NOINIT: return "NOINIT";
	case CA::INIT:   return "INIT";
	case CA::ENTER:  return "ENTER";
	case CA::LEAVE:  return "LEAVE";
	case CA::WAIT:   return "WAIT";
	default:         return "UNKNOWN";
	}
}


CA InitCA(				//инициализировать критическую секцию  status -> INIT/NOINIT
	char ipaddr[15],		//ip адрес координатора
	char resurce[20],		//имя ресурса
	int number				//номер
);
bool EnterCA(		//войти в критическую секцию status -> ENTER/WAIT -> ENTER
	CA& ca				//блок управления секцией
);
bool LeaveCA(		//покинуть критическую секцию status -> LEAVE
	CA& ca				//блок управления секцией
);
bool CloseCA(		//закрыть критическую секцию  status - > NOINIT
	CA& ca				//блок управления секцией 
);
int _tmain(int argc, _TCHAR* argv[])
{
	CA s;
	try
	{
		s = InitCA((char*)"172.20.10.8", (char*)"Z:\\file.txt", 2); 
		// айпи координатора
		// путь к папке на клиенте 
		// это локальный путь на клиенте, который передаётся координатору для идентификации или синхронизации при работе с критическим ресурсом
		while (true)
		{
			EnterCA(s);
			int k = 0;
			bool close = false;
			std::string line;
			std::ofstream ss("Z\\file.txt", std::ios::app); // сетевая папка для записи
			std::ifstream s2("Z:\\file.txt", std::ios::app); // сетевая папка для чтения
			std::cout << "1. Enter to write.\n2. Enter to read.\n3. leave section and close" << endl;
			std::cin >> k;
			if (k == 1) {
				EnterCA(s);
				for (int i = 0; i < 5; i++)
				{
					time_t rawtime;
					struct tm* timeinfo;
					time(&rawtime);
					timeinfo = localtime(&rawtime);
					if (ss.is_open())
					{
						ss << "Client: " << s.clientnumber << " " << asctime(timeinfo) << std::endl;
					}
					Sleep(1000);
				}
				LeaveCA(s);
			}
			if (k == 2) {
				if (s2.is_open()) {
					while (getline(s2, line)) {
						std::cout << line << endl;
					}
				}
			}
			if (k == 3) {
				close = true;
			}
			ss.close();
			s2.close();
			LeaveCA(s);
			if (close) break;
			Sleep(5000);
		}
		CloseCA(s);
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
		CloseCA(s);
	}
	system("pause");
	return 0;
}
CA InitCA(char ipaddr[15], char resurce[20], int number)
{
	CA result;
	strcpy(result.ipaddr, ipaddr);
	strcpy(result.resurce, resurce);
	result.clientnumber = number;
	result.status = result.INIT;
	SOCKET cC;
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());
		SOCKADDR_IN serv; 
		serv.sin_family = AF_INET; 
		serv.sin_port = htons(2000); 
		serv.sin_addr.s_addr = inet_addr(result.ipaddr); 
		int lobuf = 0; 
		int libuf = 0;
		SOCKADDR_IN clnt;
		memset(&clnt, 0, sizeof(clnt)); 
		int lc = sizeof(clnt);
		if ((lobuf = sendto(cC, (char*)&result, sizeof(result), NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR) {
			throw SetErrorMsgText("send:", WSAGetLastError());
		}
		if ((libuf = recvfrom(cC, (char*)&result, sizeof(result), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) {
			throw SetErrorMsgText("recvfrom:", WSAGetLastError());
		}
		if (closesocket(cC) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
		cout << "Client initialized with status: " << GetStatusText(result.status) << endl;
		return result;
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
		return result;
	}
}
bool EnterCA(CA& ca)
{
	SOCKET cC;
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());
		SOCKADDR_IN serv; 
		serv.sin_family = AF_INET; 
		serv.sin_port = htons(2000); 
		serv.sin_addr.s_addr = inet_addr(ca.ipaddr); 
		int lobuf = 0; 
		int libuf = 0;
		SOCKADDR_IN clnt; 
		memset(&clnt, 0, sizeof(clnt)); 
		int lc = sizeof(clnt);
		int obuf = ca.ENTER;
		CA ibuf;
		while (ca.status != ca.ENTER)
		{
			ca.status = ca.ENTER;
			if ((lobuf = sendto(cC, (char*)&ca, sizeof(ca), NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR) {
				throw SetErrorMsgText("send:", WSAGetLastError());
			}
			if ((libuf = recvfrom(cC, (char*)&ca, sizeof(ca), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) {
				throw SetErrorMsgText("recvfrom:", WSAGetLastError());
			}
			cout << "Client entering critical section, status(EnterCA): " << GetStatusText(ca.status) << endl;
			Sleep(2000);
		}
		if (closesocket(cC) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
		return true;
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
		return false;
	}
}
bool LeaveCA(CA& ca)
{
	SOCKET cC;
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());
		SOCKADDR_IN serv; 
		serv.sin_family = AF_INET; 
		serv.sin_port = htons(2000); 
		serv.sin_addr.s_addr = inet_addr(ca.ipaddr); 
		int lobuf = 0; 
		int libuf = 0;
		SOCKADDR_IN clnt; 
		memset(&clnt, 0, sizeof(clnt)); 
		int lc = sizeof(clnt);
		int obuf = ca.LEAVE;
		CA ibuf;
		while (ca.status != ca.LEAVE)
		{
			ca.status = ca.LEAVE;
			if ((lobuf = sendto(cC, (char*)&ca, sizeof(ca), NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR) {
				throw SetErrorMsgText("send:", WSAGetLastError());
			}
			if ((libuf = recvfrom(cC, (char*)&ca, sizeof(ca), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) {
				throw SetErrorMsgText("recvfrom:", WSAGetLastError());
			}
			Sleep(2000);
		}
		if (closesocket(cC) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
		cout << "Client leaving critical section, status: " << GetStatusText(ca.status) << endl;
		return true;

	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
		return false;
	}
}
bool CloseCA(CA& ca)
{
	SOCKET cC;
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		serv.sin_addr.s_addr = inet_addr(ca.ipaddr);
		int lobuf = 0;
		int libuf = 0;

		SOCKADDR_IN clnt;
		memset(&clnt, 0, sizeof(clnt));
		int lc = sizeof(clnt);
		CA ibuf;
		ca.status = ca.NOINIT;
		if ((lobuf = sendto(cC, (char*)&ca, sizeof(ca), NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR) {
			throw SetErrorMsgText("send:", WSAGetLastError());
		}
		if ((libuf = recvfrom(cC, (char*)&ca, sizeof(ca), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) {
			throw SetErrorMsgText("recvfrom:", WSAGetLastError());
		}
		if (closesocket(cC) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
		cout << "Client closed connection, status: " << GetStatusText(ca.status) << endl;
		return true;
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
		return false;
	}
	catch (const std::exception&)
	{
		return false;
	}

}