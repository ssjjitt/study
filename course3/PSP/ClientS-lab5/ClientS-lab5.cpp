#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>  // Для getaddrinfo и inet_ntop
#include <string>
#include <time.h>
#pragma comment(lib, "WS2_32.lib")

#define MAX_SIZE_OF_MSG 50

using namespace std;

string GetErrorMsgText(int code) {
    string msgText;
    switch (code)
    {
    case WSAEINTR: msgText = "WSAEINTR"; break;
    case WSAEACCES: msgText = "WSAEACCES"; break;
    case WSAEFAULT: msgText = "WSAEFAULT"; break;
    case WSAEINVAL: msgText = "WSAEINVAL"; break;
    case WSAEMFILE: msgText = "WSAEMFILE"; break;
    case WSAEWOULDBLOCK:msgText = "WSAEWOULDBLOCK"; break;
    case WSAEINPROGRESS:msgText = "WSAEINPROGRESS"; break;
    case WSAENOTSOCK:msgText = "WSAENOCTSOCK"; break;
    case WSAEDESTADDRREQ:msgText = "WSAEDESTADDRREQ"; break;
    case WSAEMSGSIZE:msgText = "WSAEMSGSIZE"; break;
    case WSAEPROTOTYPE:msgText = "WSAEPROTOTYPE"; break;
    case WSAENOPROTOOPT:msgText = "WSAENOPROTOOPT"; break;
    case WSAEPROTONOSUPPORT:msgText = "WSAEPROTONOSUPPORT"; break;
    case WSAESOCKTNOSUPPORT:msgText = "WSAESOCKTNOSUPPORT"; break;
    case WSAEOPNOTSUPP:msgText = "WSAEOPNOTSUPP"; break;
    case WSAEPFNOSUPPORT:msgText = "WSAEPFNOSUPPORT"; break;
    case WSAEAFNOSUPPORT:msgText = "WSAEAFNOSUPPORT"; break;
    case WSAEADDRINUSE:msgText = "WSAEADDRINUSE"; break;
    case WSAEADDRNOTAVAIL:msgText = "WSAEADDRNOTAVAIL"; break;
    case WSAENETDOWN:msgText = "WSAENETDOWN"; break;
    case WSAENETUNREACH:msgText = "WSAENETUNREACH"; break;
    case WSAENETRESET:msgText = "WSAENETRESET"; break;
    case WSAECONNABORTED:msgText = "WSAECONNABORTED"; break;
    case WSAECONNRESET:msgText = "WSAECONNRESET"; break;
    case WSAENOBUFS:msgText = "WSAENOBUFS"; break;
    case WSAEISCONN:msgText = "WSAEISCONN"; break;
    case WSAENOTCONN:msgText = "WSAENOTCONN"; break;
    case WSAESHUTDOWN:msgText = "WSAESHUTDOWN"; break;
    case WSAETIMEDOUT:msgText = "WSAETIMEDOUT"; break;
    case WSAECONNREFUSED:msgText = "WSAECONNREFUSED"; break;
    case WSAEHOSTDOWN:msgText = "WSAEHOSTDOWN"; break;
    case WSAEHOSTUNREACH:msgText = "WSAEHOSTUNREACH"; break;
    case WSAEPROCLIM:msgText = "WSAEPROCLIM"; break;
    case WSASYSNOTREADY:msgText = "WSASYSNOTREADY"; break;
    case WSAVERNOTSUPPORTED:msgText = "WSAVERNOTSUPPORTED"; break;
    case WSANOTINITIALISED:msgText = "WSANOTINITIALISED"; break;
    case WSAEDISCON:msgText = "WSAEDISCON"; break;
    case WSATYPE_NOT_FOUND:msgText = "WSATYPE_NOT_FOUND"; break;
    case WSAHOST_NOT_FOUND:msgText = "WSAHOST_NOT_FOUND"; break;
    case WSATRY_AGAIN:msgText = "WSATRY_AGAIN"; break;
    case WSANO_RECOVERY:msgText = "WSANO_RECOVERY"; break;
    case WSANO_DATA:msgText = "WSANO_DATA"; break;
    case WSA_INVALID_HANDLE:msgText = "WSA_INVALID_HANDLE"; break;
    case WSA_INVALID_PARAMETER:msgText = "WSA_INVALID_PARAMETER"; break;
    case WSA_IO_INCOMPLETE:msgText = "WSA_IO_INCOMPLETE"; break;
    case WSA_IO_PENDING:msgText = "WSA_IO_PENDING"; break;
    case WSA_NOT_ENOUGH_MEMORY:msgText = "WSA_NOT_ENOUGH_MEMORY"; break;
    case WSA_OPERATION_ABORTED:msgText = "WSA_OPERATION_ABORTED"; break;
    case WSAEINVALIDPROCTABLE:msgText = "WSAEINVALIDPROCTABLE"; break;
    case WSAEINVALIDPROVIDER:msgText = "WSAEINVALIDPROVIDER"; break;
    case WSAEPROVIDERFAILEDINIT:msgText = "WSAEPROVIDERFAILEDINIT"; break;
    case WSASYSCALLFAILURE:msgText = "WSASYSCALLFAILURE"; break;
    default: msgText = "***ERROR***"; break;
    }
    return msgText;
}

string SetErrorMsgText(string msgText, int code) {
    return msgText + GetErrorMsgText(code);
}

SOCKET sS;

bool GetServerByName(const char* name, const char* call, struct sockaddr* from, int* flen) {
    struct addrinfo hints, * res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; 
    hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(name, NULL, &hints, &res) != 0) {
        throw SetErrorMsgText("getaddrinfo:", WSAGetLastError());
    }

    char ip_addr[INET_ADDRSTRLEN];
    sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(res->ai_addr);
    inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ip_addr, sizeof(ip_addr));


    strcpy_s(ip_addr, "172.20.10.7");

    cout << "Server name: " << name << endl << "IP-address server: " << ip_addr << endl;


    SOCKADDR_IN server;
    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    inet_pton(AF_INET, ip_addr, &server.sin_addr);

    char message[10];
    if (sendto(sS, call, strlen(call), NULL, (const sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        throw SetErrorMsgText("sendto:", WSAGetLastError());
    }

    int buf = 0;
    if ((buf = recvfrom(sS, message, sizeof(message), NULL, (sockaddr*)&server, flen)) == SOCKET_ERROR) {
        throw SetErrorMsgText("recvfrom:", WSAGetLastError());
    }
    message[buf] = 0x00;

    cout << "Response from server: " << message << endl;
    *from = *((sockaddr*)&server);
    freeaddrinfo(res);
    return true;
}

int main() {
    WSADATA wsaData;

    try {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            throw SetErrorMsgText("Startup:", WSAGetLastError());

        if ((sS = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
            throw SetErrorMsgText("socket:", WSAGetLastError());

        sockaddr from;
        int length = sizeof(from);
        memset(&from, 0, sizeof(from));

        GetServerByName("VALERIA", "Hello", &from, &length);

        if (closesocket(sS) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("WSACleanup:", WSAGetLastError());
    }
    catch (string str) {
        printf("%s", str.c_str());
    }

    system("pause");
    return 0;
}
