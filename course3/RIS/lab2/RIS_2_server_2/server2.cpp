#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "string.h"
#include <locale>
#include "time.h"
#include "Winsock2.h"
#include <queue>
#include <tchar.h>
#include <mutex>

#pragma comment(lib, "WS2_32.lib")

using namespace std;

class Link
{
public:
    char* FileName;
    char command;
    bool UsingFile;
    SOCKADDR_IN Adr;
    HANDLE WaitEvent;
    HANDLE Thread;
    std::mutex fileMutex;
};

#define MAX_FILE 10
Link* masthr[MAX_FILE];
SOCKET sS;
int lc;

string GetErrorMsgText(int code)
{
    string msgText;
    switch (code)
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
    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
    default: msgText = "***ERROR***"; break;
    };
    return msgText;
};

string SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};

DWORD WINAPI Dispath(LPVOID lp)
{
    string str = "e";
    string str2 = "l";


    queue<SOCKADDR_IN>* q = new queue<SOCKADDR_IN>();
    int index = (int)lp;
    while (true)
    {
        WaitForSingleObject(masthr[index]->WaitEvent, INFINITE);
        if (string(1, masthr[index]->command) == str)
        {
            if (q->empty())
            {
                char buf[5];
                _itoa((masthr[index]->Adr).sin_port, buf, 10);
                sendto(sS, buf, sizeof(buf), NULL, (sockaddr*)&masthr[index]->Adr, lc);
            }
            else
            {
                const char* waitMsg = "WAIT";
                sendto(sS, waitMsg, strlen(waitMsg), NULL, (sockaddr*)&masthr[index]->Adr, lc);
            }
            q->push(masthr[index]->Adr);
        }
        else if (string(1, masthr[index]->command) == str2)
        {
            q->push(masthr[index]->Adr);
            if (string(1, masthr[index]->command) != "WAIT")
            {
                if (!q->empty())
                {
                    const char* waitMsg = "WAIT";
                    sendto(sS, waitMsg, strlen(waitMsg), NULL, (sockaddr*)&masthr[index]->Adr, lc);
                }
                q->pop();
                if (!q->empty())
                {
                    SOCKADDR_IN sc = q->front();
                    const char* enterMsg = "ENTER";
                    sendto(sS, enterMsg, strlen(enterMsg), NULL, (sockaddr*)&sc, lc);
                }
            }
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "Russian");

    std::cout << "ServerU" << endl;
    try
    {
        for (int i = 0; i < MAX_FILE; i++)
        {
            masthr[i] = NULL;
        }

        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMsgText("Startup: ", WSAGetLastError());

        if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("Socket: ", WSAGetLastError());

        SOCKADDR_IN serv;
        serv.sin_family = AF_INET;
        serv.sin_port = htons(2000);
        serv.sin_addr.s_addr = INADDR_ANY;

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw SetErrorMsgText("Bind_Server: ", WSAGetLastError());

        while (true)
        {
            SOCKADDR_IN client;
            lc = sizeof(SOCKADDR_IN);
            char ibuf[50];
            ZeroMemory(ibuf, 50);

            if ((recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&client, &lc)) == SOCKET_ERROR)
                throw SetErrorMsgText("RecvFrom: ", WSAGetLastError());

            int port = client.sin_port;
            std::cout << "Client (" << inet_ntoa(client.sin_addr) << ":" << port << "): " << ibuf << endl;

            bool create = true;
            for (int i = 0; i < MAX_FILE; i++)
            {
                if (masthr[i] != NULL)
                {
                    if (strcmp(ibuf + 5, masthr[i]->FileName) == 0)
                    {
                        create = false;
                        masthr[i]->command = ibuf[0];
                        masthr[i]->Adr = client;
                        SetEvent(masthr[i]->WaitEvent);
                        break;
                    }
                }
            }

            if (create)
            {
                Link* a = new Link();
                int pos = -1;
                bool findplace = false;
                for (int i = 0; i < MAX_FILE; i++)
                {
                    if (masthr[i] == 0)
                    {
                        findplace = true;
                        pos = i;
                        masthr[i] = a;
                        break;
                    }
                }

                if (!findplace)
                {
                    std::cout << "not create new thread" << endl;
                    break;
                }

                char* filename = new char[strlen(ibuf) - 5];
                strcpy(filename, ibuf + 5);


                a->FileName = filename;
                a->command = ibuf[0];
                a->Adr = client;
                a->UsingFile = false;
                a->WaitEvent = CreateEvent(NULL, false, true, NULL);
                a->Thread = CreateThread(NULL, NULL, &Dispath, (void*)pos, NULL, NULL);
                SetEvent(a->WaitEvent);
            }
        }

        if (closesocket(sS) == SOCKET_ERROR)
            throw SetErrorMsgText("close socket: ", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        std::cout << endl << errorMsgText;
    }

    return 0;
}
