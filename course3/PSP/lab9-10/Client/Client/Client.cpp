#include <iostream>
#include "Winsock2.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)
using namespace std;


#define INADDR_ANY        (u_long)0x00000000 //����� �����       +++ 
#define INADDR_LOOPBACK    0x7f000001        // ���������� ����� +++
#define INADDR_BROADCAST  (u_long)0xffffffff // �������������    +++  
#define INADDR_NONE        0xffffffff        // ��� ������  
#define ADDR_ANY           INADDR_ANY        // ����� �����       
#define BUFFER_SIZE 50
#define SERVER_PORT 2000

typedef struct sockaddr_in SOCKADDR_IN;    //                     +++
typedef struct sockaddr_in* PSOCKADDR_IN;
typedef struct sockaddr_in FAR* LPSOCKADDR_IN;

string GetErrorMsgText(int code)
{
    string msgText;
    switch (code) {
    case WSAEINTR:                 msgText = "������ ������� ��������";                           break;
    case WSAEACCES:                msgText = "���������� ����������";                             break;
    case WSAEFAULT:                msgText = "��������� �����";                                   break;
    case WSAEINVAL:                msgText = "������ � ��������� ";                               break;
    case WSAEMFILE:                msgText = "������� ����� ������ �������";                      break;
    case WSAEWOULDBLOCK:           msgText = "������ �������� ����������";                        break;
    case WSAEINPROGRESS:           msgText = "�������� � �������� ��������";                      break;
    case WSAEALREADY:              msgText = "�������� ��� ����������� ";                         break;
    case WSAENOTSOCK:              msgText = "����� ����� �����������   ";                        break;
    case WSAEDESTADDRREQ:          msgText = "��������� ����� ������������ ";                     break;
    case WSAEMSGSIZE:              msgText = "��������� ������� ������� ";                        break;
    case WSAEPROTOTYPE:            msgText = "������������ ��� ��������� ��� ������ ";            break;
    case WSAENOPROTOOPT:           msgText = "������ � ����� ���������";                          break;
    case WSAEPROTONOSUPPORT:       msgText = "�������� �� �������������� ";                       break;
    case WSAESOCKTNOSUPPORT:       msgText = "��� ������ �� �������������� ";                     break;
    case WSAEOPNOTSUPP:            msgText = "�������� �� �������������� ";                       break;
    case WSAEPFNOSUPPORT:          msgText = "��� ���������� �� �������������� ";                 break;
    case WSAEAFNOSUPPORT:          msgText = "��� ������� �� �������������� ����������";          break;
    case WSAEADDRINUSE:            msgText = "����� ��� ������������ ";                           break;
    case WSAEADDRNOTAVAIL:         msgText = "����������� ����� �� ����� ���� �����������";       break;
    case WSAENETDOWN:              msgText = "���� ��������� ";                                   break;
    case WSAENETUNREACH:           msgText = "���� �� ���������";                                 break;
    case WSAENETRESET:             msgText = "���� ��������� ����������";                         break;
    case WSAECONNABORTED:          msgText = "����������� ����� ����� ";                          break;
    case WSAECONNRESET:            msgText = "����� ������������� ";                              break;
    case WSAENOBUFS:               msgText = "�� ������� ������ ��� �������";                     break;
    case WSAEISCONN:               msgText = "����� ��� ���������";                               break;
    case WSAENOTCONN:              msgText = "����� �� ���������";                                break;
    case WSAESHUTDOWN:             msgText = "������ ��������� send: ����� �������� ������";      break;
    case WSAETIMEDOUT:             msgText = "���������� ���������� ��������  �������";           break;
    case WSAECONNREFUSED:          msgText = "���������� ���������  ";                            break;
    case WSAEHOSTDOWN:             msgText = "���� � ����������������� ���������";                break;
    case WSAEHOSTUNREACH:          msgText = "��� �������� ��� ����� ";                           break;
    case WSAEPROCLIM:              msgText = "������� ����� ��������� ";                          break;
    case WSASYSNOTREADY:           msgText = "���� �� �������� ";                                 break;
    case WSAVERNOTSUPPORTED:       msgText = "������ ������ ���������� ";                         break;
    case WSANOTINITIALISED:        msgText = "�� ��������� ������������� WS2_32.DLL";             break;
    case WSAEDISCON:               msgText = "����������� ����������";                            break;
    case WSATYPE_NOT_FOUND:        msgText = "����� �� ������ ";                                  break;
    case WSAHOST_NOT_FOUND:        msgText = "���� �� ������";                                    break;
    case WSATRY_AGAIN:             msgText = "������������������ ���� �� ������";                 break;
    case WSANO_RECOVERY:           msgText = "��������������  ������";                            break;
    case WSANO_DATA:               msgText = "��� ������ ������������ ����";                      break;
    case WSA_INVALID_HANDLE:       msgText = "��������� ���������� �������  � �������";           break;
    case WSA_INVALID_PARAMETER:    msgText = "���� ��� ����� ���������� � �������";               break;
    case WSA_IO_INCOMPLETE:        msgText = "������ �����-������ �� � ���������� ���������";     break;
    case WSA_IO_PENDING:           msgText = "�������� ���������� �����  ";                       break;
    case WSA_NOT_ENOUGH_MEMORY:    msgText = "�� ���������� ������ ";                             break;
    case WSA_OPERATION_ABORTED:    msgText = "�������� ���������� ";                              break;
        //case WSAINVALIDPROCTABLE:      msgText = "��������� ������ ";                                 break;
        //case WSAINVALIDPROVIDER:       msgText = "������ � ������ �������  ";                         break;
        //case WSAPROVIDERFAILEDINIT:    msgText = "���������� ���������������� ������ ";               break;
    case WSASYSCALLFAILURE:        msgText = "��������� ���������� ���������� ������ ";           break;

    default:                       msgText = "***ERROR***";                                       break;
    }
    return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
    return msgText + GetErrorMsgText(code);
}

void errorHandling(const char* msg) {
    cerr << msg << " Error code: " << WSAGetLastError() << endl;
    WSACleanup();
    exit(1);
}

bool  GetServer(
    char* call, //[in] �������� �������  
    short            port, //[in] ����� ����� �������    
    struct sockaddr* from, //[out] ��������� �� SOCKADDR_IN
    int* flen  //[out] ��������� �� ������ from 
)
{
    SOCKET sS;

    if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
        throw SetErrorMsgText("socket:", WSAGetLastError());

    int timeout = 1000;
    if (setsockopt(sS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) == SOCKET_ERROR) {
        throw SetErrorMsgText("setsockopt:", WSAGetLastError());
    }

    int optval = 1;
    if (setsockopt(sS, SOL_SOCKET, SO_BROADCAST,
        (char*)&optval, sizeof(int)) == SOCKET_ERROR)
        throw SetErrorMsgText("opt: ", WSAGetLastError());

    SOCKADDR_IN all;
    memset(&all, 0, sizeof(all));
    all.sin_family = AF_INET;
    all.sin_port = htons(port);
    all.sin_addr.s_addr = inet_addr("255.255.255.255");

    int libuf = 0;

    if ((libuf = sendto(sS, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all))) == SOCKET_ERROR)
        throw SetErrorMsgText("send: ", WSAGetLastError());
    cout << "message sent" << endl;
    char ibuf[30];
    memset(ibuf, 0, sizeof(ibuf));

    cout << "receiving..." << endl;
    for (;;) {
        if ((libuf = recvfrom(sS, ibuf, sizeof(ibuf), NULL, from, flen)) == SOCKET_ERROR) {
            if (WSAGetLastError() == WSAETIMEDOUT)
                return false;
            else throw SetErrorMsgText("recv: ", WSAGetLastError());
        }
        cout << ibuf << endl;
    }
    if (strcmp(ibuf, call) == 0) {
        if (closesocket(sS) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket: ", WSAGetLastError());
        return true;
    }
    else {
        memset(&from, 0, sizeof(from));
        return false;
    }

    if (closesocket(sS) == SOCKET_ERROR)
        throw SetErrorMsgText("closesocket: ", WSAGetLastError());

    return true;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    HANDLE lpHandles[3];

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    // ������������� �������� ������ ��������
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    si.dwFlags = STARTF_USESTDHANDLES;

    // ��������� ����� ���������� �������
    if (!CreateProcessA(
        NULL,    // ��� ��������
        (LPSTR)"ClientRandom.exe",   // ��������� ������
        NULL,    // �������� ������ �������� �� ���������
        NULL,    // �������� ������ ���������� ������ �� ���������
        TRUE,    // ����������� ����������� �������� ��������
        // ����������� ����� ���������
        CREATE_NEW_CONSOLE,  // ����� �������  
        NULL,    // ���������� ����� ��������� �������� ������
        NULL,    // ������� ���� � �������, ��� � � �������� ������
        &si,     // ��� �������� ���� - �� ���������
        &pi      // ����� ����� ����������� � ��������������
        // ������ �������� � ��� ���������� ������
    ))
    {
        cout << "Create process failed";
        return GetLastError();
    }
    lpHandles[0] = pi.hProcess;
    Sleep(100);

    STARTUPINFOA si2;
    PROCESS_INFORMATION pi2;
    // ������������� �������� ������ ��������
    ZeroMemory(&si2, sizeof(STARTUPINFOA));
    si2.cb = sizeof(STARTUPINFOA);
    si2.dwFlags = STARTF_USESTDHANDLES;

    // ��������� ����� ���������� �������
    if (!CreateProcessA(
        NULL,    // ��� ��������
        (LPSTR)"ClientTime.exe",   // ��������� ������
        NULL,    // �������� ������ �������� �� ���������
        NULL,    // �������� ������ ���������� ������ �� ���������
        TRUE,    // ����������� ����������� �������� ��������
        // ����������� ����� ���������
        CREATE_NEW_CONSOLE,  // ����� �������  
        NULL,    // ���������� ����� ��������� �������� ������
        NULL,    // ������� ���� � �������, ��� � � �������� ������
        &si2,     // ��� �������� ���� - �� ���������
        &pi2      // ����� ����� ����������� � ��������������
        // ������ �������� � ��� ���������� ������
    ))
    {
        cout << "Create process failed";
        return GetLastError();
    }
    lpHandles[1] = pi2.hProcess;



    
    WaitForSingleObject(pi.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    WaitForMultipleObjects(3, lpHandles, TRUE, INFINITE);

    

    return 0;
}