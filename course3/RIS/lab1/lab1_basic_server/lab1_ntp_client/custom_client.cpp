#include "iostream"
#include "Winsock2.h"
#include "ctime"
#include <chrono>
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
using namespace chrono;

struct TimeRequest {
	long clientTimeSent;
};

struct TimeResponse {
	long serverTimeReceived;
};

string GetErrorMsgText(int code)
{
	string msgText;

	switch (code)
	{
	case WSAEINTR:				 msgText = "������ ������� ��������\n";						  break;
	case WSAEACCES:				 msgText = "���������� ����������\n";						  break;
	case WSAEFAULT:				 msgText = "��������� �����\n";								  break;
	case WSAEINVAL:				 msgText = "������ � ���������\n";							  break;
	case WSAEMFILE:				 msgText = "������� ����� ������ �������\n";				  break;
	case WSAEWOULDBLOCK:		 msgText = "������ �������� ����������\n";					  break;
	case WSAEINPROGRESS:		 msgText = "�������� � �������� ��������\n";				  break;
	case WSAEALREADY: 			 msgText = "�������� ��� �����������\n";					  break;
	case WSAENOTSOCK:   		 msgText = "����� ����� �����������\n";						  break;
	case WSAEDESTADDRREQ:		 msgText = "��������� ����� ������������\n";				  break;
	case WSAEMSGSIZE:  			 msgText = "��������� ������� �������\n";				      break;
	case WSAEPROTOTYPE:			 msgText = "������������ ��� ��������� ��� ������\n";		  break;
	case WSAENOPROTOOPT:		 msgText = "������ � ����� ���������\n";					  break;
	case WSAEPROTONOSUPPORT:	 msgText = "�������� �� ��������������\n";					  break;
	case WSAESOCKTNOSUPPORT:	 msgText = "��� ������ �� ��������������\n";				  break;
	case WSAEOPNOTSUPP:			 msgText = "�������� �� ��������������\n";					  break;
	case WSAEPFNOSUPPORT:		 msgText = "��� ���������� �� ��������������\n";			  break;
	case WSAEAFNOSUPPORT:		 msgText = "��� ������� �� �������������� ����������\n";	  break;
	case WSAEADDRINUSE:			 msgText = "����� ��� ������������\n";						  break;
	case WSAEADDRNOTAVAIL:		 msgText = "����������� ����� �� ����� ���� �����������\n";	  break;
	case WSAENETDOWN:			 msgText = "���� ���������\n";								  break;
	case WSAENETUNREACH:		 msgText = "���� �� ���������\n";							  break;
	case WSAENETRESET:			 msgText = "���� ��������� ����������\n";					  break;
	case WSAECONNABORTED:		 msgText = "����������� ����� �����\n";						  break;
	case WSAECONNRESET:			 msgText = "����� �������������\n";							  break;
	case WSAENOBUFS:			 msgText = "�� ������� ������ ��� �������\n";				  break;
	case WSAEISCONN:			 msgText = "����� ��� ���������\n";							  break;
	case WSAENOTCONN:			 msgText = "����� �� ���������\n";							  break;
	case WSAESHUTDOWN:			 msgText = "������ ��������� send: ����� �������� ������\n";  break;
	case WSAETIMEDOUT:			 msgText = "���������� ���������� ��������  �������\n";		  break;
	case WSAECONNREFUSED:		 msgText = "���������� ���������\n";						  break;
	case WSAEHOSTDOWN:			 msgText = "���� � ����������������� ���������\n";			  break;
	case WSAEHOSTUNREACH:		 msgText = "��� �������� ��� �����\n";						  break;
	case WSAEPROCLIM:			 msgText = "������� ����� ���������\n";						  break;
	case WSASYSNOTREADY:		 msgText = "���� �� ��������\n";							  break;
	case WSAVERNOTSUPPORTED:	 msgText = "������ ������ ����������\n";					  break;
	case WSANOTINITIALISED:		 msgText = "�� ��������� ������������� WS2_32.DLL\n";		  break;
	case WSAEDISCON:			 msgText = "����������� ����������\n";						  break;
	case WSATYPE_NOT_FOUND:		 msgText = "����� �� ������\n";								  break;
	case WSAHOST_NOT_FOUND:		 msgText = "���� �� ������\n";								  break;
	case WSATRY_AGAIN:			 msgText = "������������������ ���� �� ������\n";			  break;
	case WSANO_RECOVERY:		 msgText = "�������������� ������\n";						  break;
	case WSANO_DATA:			 msgText = "��� ������ ������������ ����\n";				  break;
	case WSA_INVALID_HANDLE:	 msgText = "��������� ���������� �������  � �������\n";		  break;
	case WSA_INVALID_PARAMETER:	 msgText = "���� ��� ����� ���������� � �������\n";			  break;
	case WSA_IO_INCOMPLETE:		 msgText = "������ �����-������ �� � ���������� ���������\n"; break;
	case WSA_IO_PENDING:		 msgText = "�������� ���������� �����\n";					  break;
	case WSA_NOT_ENOUGH_MEMORY:	 msgText = "�� ���������� ������\n";						  break;
	case WSA_OPERATION_ABORTED:	 msgText = "�������� ����������\n";							  break;
	case WSAEINVALIDPROCTABLE:	 msgText = "��������� ������\n";							  break;
	case WSAEINVALIDPROVIDER:	 msgText = "������ � ������ �������\n";						  break;
	case WSAEPROVIDERFAILEDINIT: msgText = "���������� ���������������� ������\n";			  break;
	case WSASYSCALLFAILURE:		 msgText = "��������� ���������� ���������� ������\n";		  break;
	default:					 msgText = "Error\n";										  break;
	};
	return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	string defaultIP = "172.20.10.8";
	string serverIP;

	if (argc == 2) {
		serverIP = argv[1];
		cout << "Using server IP from argument: " << serverIP << endl;
	}
	else {
		serverIP = defaultIP;
		cout << "No server IP argument passed. Using default IP: " << serverIP << endl;
	}

	SOCKET clientSocket;
	WSADATA wsaData;
	SOCKADDR_IN serverAddr;

	cout << "UDP Time Sync Client Running..." << endl;

	try {
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(2000);
		serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());

		TimeRequest timeRequest;
		TimeResponse timeResponse;

		for (int i = 0; i < 5; i++) {
			timeRequest.clientTimeSent = time(nullptr);
			cout << "Client time sent: " << timeRequest.clientTimeSent << endl;

			auto start = system_clock::now(); // ����� �������� �������
			if (sendto(clientSocket, (char*)&timeRequest, sizeof(timeRequest), 0, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
				throw SetErrorMsgText("SendTo: ", WSAGetLastError());

			int serverAddrSize = sizeof(serverAddr);
			if (recvfrom(clientSocket, (char*)&timeResponse, sizeof(timeResponse), 0, (sockaddr*)&serverAddr, &serverAddrSize) == SOCKET_ERROR)
				throw SetErrorMsgText("RecvFrom: ", WSAGetLastError());

			auto end = system_clock::now(); // ����� ��������� ������
			auto roundTripTime = duration_cast<milliseconds>(end - start).count();
			cout << "Server time received: " << timeResponse.serverTimeReceived << endl;

			long serverTimeEstimate = timeRequest.clientTimeSent + roundTripTime / 2;
			cout << "Round-Trip Time: " << roundTripTime << " ms" << endl;
			cout << "Estimated server time (corrected): " << serverTimeEstimate << endl;

			Sleep(1000); // 1 ������� �������� ����� ���������
		}

		if (closesocket(clientSocket) == SOCKET_ERROR)
			throw SetErrorMsgText("Close socket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsg) {
		cout << errorMsg << endl;
	}

	return 0;
}
