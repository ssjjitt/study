#pragma comment(lib, "WS2_32.lib") 
#pragma warning(disable: 4996)
#include "Winsock2.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int countServers = 0;

bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen);
bool PutAnswerToClient(char* name, short port, struct sockaddr* to, int* lto);
void GetServer(char* call, short port, struct sockaddr* from, int* flen);

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

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SOCKET sS;
    WSADATA wsaData;

    SOCKADDR_IN client;
    int clientSize = sizeof(client);
    char name[] = "Hello";
    char hostname[32];

    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("Startup:", WSAGetLastError());

        cout << "Checking for other servers..." << endl;
        GetServer(name, 2000, (sockaddr*)&client, &clientSize);


        if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw  SetErrorMsgText("socket:", WSAGetLastError());


        SOCKADDR_IN serv;
        serv.sin_family = AF_INET;
        serv.sin_port = htons(2000);
        serv.sin_addr.s_addr = INADDR_ANY;

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw  SetErrorMsgText("bind:", WSAGetLastError());

        SOCKADDR_IN clientB;
        int clientSize = sizeof(clientB);

        if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR)
            throw SetErrorMsgText("gethostname:", WSAGetLastError());
        cout << "Server name: " << hostname << endl;

        while (true)
        {
            if (GetRequestFromClient(name, sS, (SOCKADDR*)&clientB, &clientSize))
            {
                cout << endl;
                cout << "Client socket:" << endl;
                cout << "IP: " << inet_ntoa(clientB.sin_addr) << endl;
                cout << "Port: " << htons(clientB.sin_port) << endl;
                cout << "Hostname: " << gethostbyaddr((char*)&clientB.sin_addr, sizeof(clientB.sin_addr), AF_INET)->h_name << endl << endl;
                cout << endl;

                if (PutAnswerToClient(name, sS, (SOCKADDR*)&clientB, &clientSize))
                {
                    cout << "Success!" << endl;
                }
            }
            else
            {
                cout << "Wrong call name!" << endl;
            }
        }

        if (closesocket(sS) == SOCKET_ERROR)
            throw  SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw  SetErrorMsgText("Cleanup:", WSAGetLastError());

    }
    catch (string errorMsgText)
    {
        std::cout << endl << "WSAGetLastError: " << errorMsgText;
    }

}


bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen)
{
    char buf[50] = "";
    int lenght;
    cout << "\nWait message..." << endl;

    while (true)
    {
        if (lenght = recvfrom(port, buf, sizeof(buf), NULL, from, flen) == SOCKET_ERROR)
        {
            cout << "Error:" << endl;
            if (WSAGetLastError() == WSAETIMEDOUT)
                return false;
            else
                throw SetErrorMsgText("Recvfrom: ", WSAGetLastError());
        }
        return strcmp(buf, name) == 0;
    }
}

bool PutAnswerToClient(char* name, short port, struct sockaddr* to, int* lto)
{
    int lenghts = strlen(name);
    return sendto(port, name, lenghts + 1, NULL, to, *lto);
}

void GetServer(char* call, short port, struct sockaddr* from, int* flen)
{
    SOCKET cC;
    SOCKADDR_IN all;

    int timeout = 5000;

    int optval = 1;
    char buf[50];

    try
    {
        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw  SetErrorMsgText("socket:", WSAGetLastError());


        if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
            throw  SetErrorMsgText("setsocketopt:", WSAGetLastError());
        if (setsockopt(cC, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(int)) == SOCKET_ERROR)
            throw  SetErrorMsgText("setsocketopt:", WSAGetLastError());

        all.sin_family = AF_INET;
        all.sin_port = htons(port);
        // all.sin_addr.s_addr = inet_addr("172.20.10.7"); 
        all.sin_addr.s_addr = INADDR_BROADCAST;

        if (sendto(cC, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all)) == SOCKET_ERROR)
            throw SetErrorMsgText("sendto:", WSAGetLastError());
        if (recvfrom(cC, buf, sizeof(buf), NULL, from, flen) == SOCKET_ERROR)
            throw  SetErrorMsgText("recvfrom:", WSAGetLastError());

        if (strcmp(call, buf) == 0)
        {
            countServers++;
            cout << "There's a server with the same callsign!" << endl;
            cout << "Count:" << countServers << endl;
            cout << "IP: " << inet_ntoa(((SOCKADDR_IN*)from)->sin_addr) << endl;
            cout << "Port: " << ntohs(((struct sockaddr_in*)from)->sin_port) << endl;
            cin.get();
            exit(0);
        }
    }
    catch (string errorMsgText)
    {
        if (WSAGetLastError() == WSAETIMEDOUT)
        {
            cout << "Number of servers with the same callsign: " << countServers << endl;
            if (closesocket(cC) == SOCKET_ERROR)
                throw SetErrorMsgText("closesocket: ", WSAGetLastError());
        }
        else throw SetErrorMsgText("GetServer:", WSAGetLastError());
    }
}