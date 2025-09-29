#include <iostream>
#include <list>        
#include <stdio.h>
#include <tchar.h>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)
using namespace std;

#define INADDR_ANY        (u_long)0x00000000 //����� �����       +++ 
#define INADDR_LOOPBACK    0x7f000001        // ���������� ����� +++
#define INADDR_BROADCAST  (u_long)0xffffffff // �������������    +++  
#define INADDR_NONE        0xffffffff        // ��� ������  
#define ADDR_ANY           INADDR_ANY        // ����� �����       
#define AS_SQ 10


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
    case WSAEINVALIDPROCTABLE:         msgText = "WSAEINVALIDPROCTABLE";        break;
    case WSAEINVALIDPROVIDER:          msgText = "WSAEINVALIDPROVIDER";         break;
    case WSAEPROVIDERFAILEDINIT:         msgText = "WSAEPROVIDERFAILEDINIT";        break;
    default:                       msgText = "***ERROR***";                                       break;
    }
    return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
    return msgText + GetErrorMsgText(code);
}

string  SetPipeError(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};

SOCKET sS;
SOCKET csS; //����� ��� �������
SOCKET ccS;
SOCKADDR_IN consolePrms;      // ���������  ������ 
int consoleLprms;     // ����� prms
int serverPort;
char dllName[50];
char namedPipeName[10];

volatile long connectionCount = 0;
volatile long sayNoCount = 0;
volatile long successConnections = 0;
volatile long currentActiveConnections = 0;

HANDLE hAcceptServer, hConsolePipe, hGarbageCleaner, hDispatchServer, hResponseServer;
HANDLE hClientConnectedEvent = CreateEvent(NULL,
    FALSE,
    FALSE,
    L"ClientConnected");

DWORD WINAPI AcceptServer(LPVOID pPrm);
DWORD WINAPI ConsolePipe(LPVOID pPrm);
DWORD WINAPI GarbageCleaner(LPVOID pPrm);
DWORD WINAPI DispatchServer(LPVOID pPrm);
DWORD WINAPI ResponseServer(LPVOID pPrm);

CRITICAL_SECTION scListContact;

enum TalkersCommand
{
    START, STOP, EXIT, STATISTICS, WAIT, SHUTDOWN, GETCOMMAND, LOAD_LIB, UNLOAD_LIB
};
volatile TalkersCommand  previousCommand = GETCOMMAND;

struct Contact         // ������� ������ �����������       
{
    enum TE {               // ���������  ������� �����������  
        EMPTY,              // ������ ������� ������ ����������� 
        ACCEPT,             // ��������� (accept), �� �� �������������
        CONTACT             // ������� �������������� �������  
    }    type;     // ��� �������� ������ ����������� 
    enum ST {               // ��������� �������������� �������  
        WORK,               // ���� ����� ������� � ��������
        ABORT,              // ������������� ������ ���������� �� ��������� 
        TIMEOUT,            // ������������� ������ ���������� �� ������� 
        FINISH              // ������������� ������ ����������  ��������� 
    }      sthread; // ���������  �������������� ������� (������)

    SOCKET      s;         // ����� ��� ������ ������� � ��������
    SOCKADDR_IN prms;      // ���������  ������ 
    int         lprms;     // ����� prms 
    HANDLE      hthread;   // handle ������ (��� ��������) 
    HANDLE      htimer;    // handle �������
    HANDLE      serverHThread;

    char msg[50];           // ��������� 
    char srvname[15];       //  ������������ �������������� ������� 

    Contact(TE t = EMPTY, const char* namesrv = "")
    {
        memset(&prms, 0, sizeof(SOCKADDR_IN));
        lprms = sizeof(SOCKADDR_IN);
        type = t;
        strcpy(srvname, namesrv);
        msg[0] = 0;
    };

    void SetST(ST sth, const char* m = "")
    {
        sthread = sth;
        strcpy(msg, m);
    }
};
typedef list<Contact> ListContact;

ListContact contacts;


bool AcceptCycle(int sq)
{
    bool rc = false;
    Contact c(Contact::ACCEPT, "EchoServer");
    while (sq-- > 0 && !rc)
    {
        if ((c.s = accept(sS, (sockaddr*)&c.prms, &c.lprms)) == INVALID_SOCKET)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
                throw  SetErrorMsgText("accept:", WSAGetLastError());
        }
        else
        {
            rc = true;
            EnterCriticalSection(&scListContact);
            contacts.push_front(c);
            LeaveCriticalSection(&scListContact);
            puts("contact connected");
            InterlockedIncrement(&connectionCount);
        }
    }
    return rc;
};

void openSocket()
{
    SOCKADDR_IN serv;
    sockaddr_in clnt;
    u_long nonblk = 1;

    if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
        throw  SetErrorMsgText("socket:", WSAGetLastError());

    int lclnt = sizeof(clnt);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(serverPort);
    serv.sin_addr.s_addr = INADDR_ANY;

    if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
        throw  SetErrorMsgText("bind:", WSAGetLastError());
    if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
        throw  SetErrorMsgText("listen:", WSAGetLastError());
    if (ioctlsocket(sS, FIONBIO, &nonblk) == SOCKET_ERROR)
        throw SetErrorMsgText("ioctlsocket:", WSAGetLastError());
}

void closeSocket()
{
    if (closesocket(sS) == SOCKET_ERROR)
        throw  SetErrorMsgText("closesocket:", WSAGetLastError());
}

void CommandsCycle(TalkersCommand& cmd)
{
    int  sq = 0;
    while (cmd != EXIT)
    {
        switch (cmd)
        {
        case START: cmd = GETCOMMAND;
            if (previousCommand != START)
            {
                sq = AS_SQ;
                puts("Start command");
                openSocket();
                previousCommand = START;
            }
            else puts("start already in use");
            break;
        case STOP:  cmd = GETCOMMAND;
            if (previousCommand != STOP)
            {
                sq = 0;
                puts("Stop command");
                closeSocket();
                previousCommand = STOP;
            }
            else puts("stop already in use");

            break;
        case WAIT:  cmd = GETCOMMAND;
            sq = 0;
            puts("Wait command\n" \
                "socket closed for waiting other clients");
            closeSocket();
            while (contacts.size() != 0);
            printf("size of contacts %d\n", contacts.size());
            cmd = START;
            previousCommand = WAIT;
            puts("socket is open");

            break;
        case SHUTDOWN:
            sq = 0;
            puts("SHUTDOWN command\n" \
                "........shutting down...........");
            closeSocket();
            while (contacts.size() != 0);
            printf("size of contacts %d\n", contacts.size());
            cmd = EXIT;
            break;
        case GETCOMMAND:  cmd = GETCOMMAND;

            break;
        };
        if (cmd != STOP)
        {

            if (AcceptCycle(sq))
            {
                cmd = GETCOMMAND;
                SetEvent(hClientConnectedEvent);
            }
            else SleepEx(5000, TRUE);
        }
    };
};

DWORD WINAPI AcceptServer(LPVOID pPrm)
{
    DWORD rc = 0;
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("Startup:", WSAGetLastError());

        CommandsCycle(*((TalkersCommand*)pPrm));

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        printf("\n%s\n", errorMsgText.c_str());
    }
    puts("shutdown acceptServer");
    ExitThread(rc);
}

TalkersCommand set_param(char* param)
{
    /*if (!strcmp(param, "START")) return START;
    if (!strcmp(param, "STOP")) return STOP;
    if (!strcmp(param, "EXIT")) return EXIT;
    if (!strcmp(param, "WAIT")) return WAIT;
    if (!strcmp(param, "SHUTDOWN")) return SHUTDOWN;
    if (!strcmp(param, "STATISTICS")) return STATISTICS;
    if (!strcmp(param, "GETCOMMAND")) return GETCOMMAND;*/
    if (!strcmp(param, "1")) return START;
    if (!strcmp(param, "2")) return STOP;
    if (!strcmp(param, "3")) return EXIT;
    if (!strcmp(param, "4")) return STATISTICS;
    if (!strcmp(param, "5")) return WAIT;
    if (!strcmp(param, "6")) return SHUTDOWN;
    if (!strcmp(param, "4")) return STATISTICS;
    if (!strcmp(param, "7")) return GETCOMMAND;
}

typedef void* (*FUNCTION)(char*, LPVOID);
FUNCTION ts;

HMODULE st;
SOCKET sSUDP;


void CALLBACK ASWTimer(LPVOID Prm, DWORD, DWORD)
{
    Contact* contact = (Contact*)(Prm);
    cout << ("Connection was terminated by timer") << endl;
    TerminateThread(contact->serverHThread, NULL);
    send(contact->s, "TimeOUT", strlen("TimeOUT") + 1, NULL);
    EnterCriticalSection(&scListContact);
    CancelWaitableTimer(contact->htimer);
    contact->type = contact->EMPTY;
    contact->sthread = contact->TIMEOUT;
    LeaveCriticalSection(&scListContact);
}

DWORD WINAPI DispatchServer(LPVOID pPrm)
{
    DWORD rc = 0;
    TalkersCommand& command = *(TalkersCommand*)pPrm;
    while (command != EXIT)
    {
        if (command == STOP) continue;
        WaitForSingleObject(hClientConnectedEvent, INFINITE);
        ResetEvent(hClientConnectedEvent);
        while (true)
        {
            EnterCriticalSection(&scListContact);
            for (auto client = contacts.begin(); client != contacts.end(); client++)
            {
                if (client->type == client->ACCEPT)
                {

                    char serviceType[10];
                    if (recv(client->s, serviceType, sizeof(serviceType), NULL) < 1)
                        continue;

                    cout << "New command - " << serviceType << endl;

                    strcpy(client->msg, serviceType);

                    if (!strcmp(client->msg, "close"))
                    {
                        if ((send(client->s, "echo: close", strlen("echo: close") + 1, NULL)) == SOCKET_ERROR)
                            throw  SetErrorMsgText("send:", WSAGetLastError());
                        client->sthread = client->FINISH;
                        client->type = client->EMPTY;
                        continue;
                    }
                    if (strcmp(client->msg, "Echo") && strcmp(client->msg, "Time") && strcmp(client->msg, "Random"))
                    {
                        if ((send(client->s, "ErrorInquiry", strlen("ErrorInquiry") + 1, NULL)) == SOCKET_ERROR)
                            throw  SetErrorMsgText("send:", WSAGetLastError());
                        client->sthread = client->ABORT;
                        client->type = client->EMPTY;
                        if (closesocket(client->s) == SOCKET_ERROR)
                            throw  SetErrorMsgText("closesocket:", WSAGetLastError());
                    }
                    else
                    {
                        client->type = client->CONTACT;
                        client->hthread = hAcceptServer;
                        client->htimer = CreateWaitableTimer(0, FALSE, 0);
                        __int64         qwDueTime;
                        LARGE_INTEGER   liDueTime;
                        qwDueTime = -20 * 10000000;
                        liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
                        liDueTime.HighPart = (LONG)(qwDueTime >> 32);
                        
                        SetWaitableTimer(client->htimer, &liDueTime, 0, ASWTimer, (LPVOID) & (*client), FALSE);
                        client->serverHThread = ts(serviceType, (LPVOID) & (*client));
                    }
                }
            }
            LeaveCriticalSection(&scListContact);
            SleepEx(0, TRUE);
        }
    }
    puts("shutdown dispatchServer");
    ExitThread(rc);
}

DWORD WINAPI GarbageCleaner(LPVOID pPrm)
{
    DWORD rc = 0;
    while (*((TalkersCommand*)pPrm) != EXIT)
    {
        int listSize = 0;
        int howMuchClean = 0;
        if (contacts.size() != 0)
        {
            for (auto i = contacts.begin(); i != contacts.end();)
            {
                if (i->type == i->EMPTY)
                {
                    EnterCriticalSection(&scListContact);
                    if (i->sthread == i->FINISH)
                        InterlockedIncrement(&successConnections);
                    if (i->sthread == i->ABORT || i->sthread == i->TIMEOUT)
                        InterlockedIncrement(&sayNoCount);
                    i = contacts.erase(i);
                    howMuchClean++;
                    listSize = contacts.size();
                    cout << "Garbage" << endl;
                    LeaveCriticalSection(&scListContact);
                }
                else ++i;
            }
        }
    }
    puts("shutdown garbageCleaner");
    ExitThread(rc);
}


bool AcceptConsoleCycle(int sq)
{
    bool rc = false;
    sockaddr_in clnt;
    int clntLength = sizeof(clnt);
    while (sq-- > 0 && !rc)
    {
        if ((ccS = accept(csS, (sockaddr*)&clnt, &clntLength)) == INVALID_SOCKET)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
                throw  SetErrorMsgText("accept:", WSAGetLastError());
        }
        else
        {
            rc = true;
            puts("Console connected\n");
        }
    }
    return rc;
};

void openConsoleSocket()
{
    SOCKADDR_IN serv;
    sockaddr_in clnt;
    u_long nonblk = 1;

    if ((csS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
        throw  SetErrorMsgText("socket:", WSAGetLastError());

    int lclnt = sizeof(clnt);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(2001);
    serv.sin_addr.s_addr = INADDR_ANY;

    if (bind(csS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
        throw  SetErrorMsgText("bind:", WSAGetLastError());
    if (listen(csS, SOMAXCONN) == SOCKET_ERROR)
        throw  SetErrorMsgText("listen:", WSAGetLastError());
    if (ioctlsocket(csS, FIONBIO, &nonblk) == SOCKET_ERROR)
        throw SetErrorMsgText("ioctlsocket:", WSAGetLastError());
}

void closeConsoleSocket()
{
    if (closesocket(csS) == SOCKET_ERROR)
        throw  SetErrorMsgText("closesocket:", WSAGetLastError());
}

DWORD WINAPI ConsolePipe(LPVOID pPrm) {

    TalkersCommand& param = *((TalkersCommand*)pPrm);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
        throw  SetErrorMsgText("Startup:", WSAGetLastError());

    openConsoleSocket();

    while (param != EXIT && param != SHUTDOWN) {
        if (AcceptConsoleCycle(10)) {
            char rbuf[10];
            while (true) {
                if (recv(ccS, rbuf, sizeof(rbuf), NULL) < 1)
                    continue;
                else {
                    printf("remote console message:  %s\n", rbuf);
                    param = set_param(rbuf);
                    if ((strcmp(rbuf, "0") == 0)) {
                        cout << "RsConsole disconnected\n";
                        break;
                    }

                    if (param == STATISTICS)
                    {
                        char sendStastistics[200];
                        sprintf(sendStastistics, "\nStatistics\n"\
                            "count of connectings :    %d\n" \
                            "count of denides:        %d\n" \
                            "success end:             %d\n" \
                            "count of active connections : %d\n" \
                            "", connectionCount, sayNoCount, successConnections, contacts.size());
                        if(send(ccS, sendStastistics, sizeof(sendStastistics), NULL) == SOCKET_ERROR)
                            throw SetErrorMsgText("send:", WSAGetLastError());
                    }

                    if (param != STATISTICS) {
                        if (send(ccS, rbuf, sizeof(rbuf), NULL) == SOCKET_ERROR)
                            throw SetErrorMsgText("send:", WSAGetLastError());
                    }
                    if (param == EXIT || param == SHUTDOWN)
                    {
                        break;
                    }
                }
                {
                    //int bytesRead = recv(ccS, command, sizeof(command) - 1, 0);
                    //if (bytesRead == SOCKET_ERROR) {
                    //    int errorCode = WSAGetLastError();
                    //    if (errorCode != WSAEWOULDBLOCK) {
                    //        std::cerr << "������ recv: " << errorCode << std::endl;
                    //        closeConsoleSocket();
                    //        return 1;
                    //    }
                    //}
                    //else if (bytesRead == 0) {
                    //    std::cout << "������ ������ ����������." << std::endl;
                    //    closeConsoleSocket();
                    //    return 0;
                    //}
                    //else {
                    //    command[bytesRead] = '\0'; // ���������� ������
                    //    std::cout << "����� ���������: " << command << std::endl;
                    //}
                }
                //closeConsoleSocket();
                //return 0;
            }
            
        }
    }
    if (WSACleanup() == SOCKET_ERROR)
        throw SetErrorMsgText("Cleanup:", WSAGetLastError());

}

DWORD WINAPI ConsolePipePipe(LPVOID pPrm)
{
    DWORD rc = 0;
    char rbuf[100];
    DWORD dwRead, dwWrite;
    HANDLE hPipe;
    try
    {
        char namedPipeConnectionString[50];
        sprintf(namedPipeConnectionString, "\\\\.\\pipe\\%s", namedPipeName);
        if ((hPipe = CreateNamedPipeA(namedPipeConnectionString,
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_WAIT,
            1, NULL, NULL,
            INFINITE, NULL)) == INVALID_HANDLE_VALUE)
            throw SetPipeError("create:", GetLastError());
        if (!ConnectNamedPipe(hPipe, NULL))
            throw SetPipeError("connect:", GetLastError());
        TalkersCommand& param = *((TalkersCommand*)pPrm);

        while (param != EXIT)
        {
            puts("Connecting to Named Pipe Client ...");
            ConnectNamedPipe(hPipe, NULL);
            while (ReadFile(hPipe, rbuf, sizeof(rbuf), &dwRead, NULL))
            {
                printf("remote console message:  %s\n", rbuf);
                param = set_param(rbuf);

                if (param == STATISTICS)
                {
                    char sendStastistics[200];
                    sprintf(sendStastistics, "\nStatistics\n"\
                        "count of connectings :    %d\n" \
                        "count of denides:        %d\n" \
                        "success end:             %d\n" \
                        "count of active connections : %d\n" \
                        "", connectionCount, sayNoCount, successConnections, contacts.size());
                    WriteFile(hPipe, sendStastistics, sizeof(sendStastistics), &dwWrite, NULL);
                }

                if (param != STATISTICS)
                    WriteFile(hPipe, rbuf, strlen(rbuf) + 1, &dwWrite, NULL);
                if (param == EXIT || param == SHUTDOWN)
                {
                    break;
                }
            }
            DisconnectNamedPipe(hPipe);
            if (param == EXIT || param == SHUTDOWN)
            {
                break;
            }
        }
    }
    catch (string ErrorPipeText)
    {
        printf("\n%s\n", ErrorPipeText.c_str());
        return -1;
    }
    CloseHandle(hPipe);
    puts("shutdown ConsolePipe");
    ExitThread(rc);
}



bool GetRequestFromClient(char* name, short port, SOCKADDR_IN* from, int* flen)
{
    SOCKADDR_IN clnt;
    int lc = sizeof(clnt);
    ZeroMemory(&clnt, lc);
    char ibuf[500];
    int  lb = 0;
    int optval = 1;
    int TimeOut = 10;
    setsockopt(sSUDP, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int));
    setsockopt(sSUDP, SOL_SOCKET, SO_RCVTIMEO, (char*)&TimeOut, sizeof(TimeOut));
    while (true)
    {
        if ((lb = recvfrom(sSUDP, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) return false;
        ibuf[lb] = '\0';
        cout << endl << ibuf << endl;
        if (!strcmp(name, ibuf))
        {
            *from = clnt;
            *flen = lc;
            return true;
        }
        puts("\nbad name");
    }

}

bool PutAnswerToClient(char* name, sockaddr* to, int* lto, bool allowedToConnect)
{
    char msgOk[] = "You can connect to server ";
    char msgNotOk[] = "You can't connect to server now";
    if (allowedToConnect) {
        if ((sendto(sSUDP, msgOk, sizeof(msgOk) + 1, NULL, to, *lto)) == SOCKET_ERROR)
            throw  SetErrorMsgText("sendto:", WSAGetLastError());
    }
    else {
        if ((sendto(sSUDP, msgNotOk, sizeof(msgNotOk) + 1, NULL, to, *lto)) == SOCKET_ERROR)
            throw  SetErrorMsgText("sendto:", WSAGetLastError());
    }
    
    return false;
}

DWORD WINAPI ResponseServer(LPVOID pPrm)
{
    DWORD rc = 0;
    WSADATA wsaData;
    SOCKADDR_IN serv;
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
        throw  SetErrorMsgText("Startup:", WSAGetLastError());
    if ((sSUDP = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
        throw  SetErrorMsgText("socket:", WSAGetLastError());
    serv.sin_family = AF_INET;
    serv.sin_port = htons(serverPort);
    serv.sin_addr.s_addr = INADDR_ANY;

    if (bind(sSUDP, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
        throw  SetErrorMsgText("bind:", WSAGetLastError());


    SOCKADDR_IN some_server;
    int serverSize = sizeof(some_server);

    SOCKADDR_IN from;
    int lc = sizeof(from);
    ZeroMemory(&from, lc);
    int numberOfClients = 0;
    while (*(TalkersCommand*)pPrm != EXIT)
    {
        try
        {
            if (GetRequestFromClient((char*)"myConcServer", serverPort, &from, &lc))
            {
                printf("Request from Client for connection: %d, port: %d, address: %s\n", ++numberOfClients, htons(from.sin_port), inet_ntoa(from.sin_addr));
                if(previousCommand != STOP && previousCommand != WAIT)
                    PutAnswerToClient((char*)"myConcServer", (sockaddr*)&from, &lc, true);
                else
                    PutAnswerToClient((char*)"myConcServer", (sockaddr*)&from, &lc, false);
            }
        }
        catch (string errorMsgText)
        {
            printf("\n%s", errorMsgText.c_str());
        }
    }
    if (closesocket(sSUDP) == SOCKET_ERROR)
        throw  SetErrorMsgText("closesocket:", WSAGetLastError());
    if (WSACleanup() == SOCKET_ERROR)
        throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
    ExitThread(rc);
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");


    if (argc == 2)
    {
        serverPort = atoi(argv[1]);
        strcpy(dllName, "ServiceLibrary.dll");
        strcpy(namedPipeName, "Tube");
    }
    else if (argc == 3)
    {
        serverPort = atoi(argv[1]);
        strcpy(dllName, argv[2]);
        strcpy(namedPipeName, "Tube");
    }
    else if (argc == 4)
    {
        serverPort = atoi(argv[1]);
        strcpy(dllName, argv[2]);
        strcpy(namedPipeName, argv[3]);
    }
    else {
        serverPort = 2000;
        strcpy(dllName, "ServiceLibrary.dll");
        strcpy(namedPipeName, "Tube");
    }
    printf("Server port %d\n", serverPort);

    st = LoadLibraryA(dllName);
    ts = (HANDLE(*)(char*, LPVOID))GetProcAddress(st, "SSS");

    volatile TalkersCommand  cmd = START;

    InitializeCriticalSection(&scListContact);

    hAcceptServer = CreateThread(NULL, NULL, AcceptServer,
        (LPVOID)&cmd, NULL, NULL);
    hDispatchServer = CreateThread(NULL, NULL, DispatchServer,
        (LPVOID)&cmd, NULL, NULL);
    hGarbageCleaner = CreateThread(NULL, NULL, GarbageCleaner,
        (LPVOID)&cmd, NULL, NULL);
    hConsolePipe = CreateThread(NULL, NULL, ConsolePipe,
        (LPVOID)&cmd, NULL, NULL);
    hResponseServer = CreateThread(NULL, NULL, ResponseServer,
        (LPVOID)&cmd, NULL, NULL);

    SetThreadPriority(hGarbageCleaner, THREAD_PRIORITY_IDLE);
    SetThreadPriority(hDispatchServer, THREAD_PRIORITY_NORMAL);
    SetThreadPriority(hAcceptServer, THREAD_PRIORITY_HIGHEST);


    WaitForSingleObject(hAcceptServer, INFINITE);
    CloseHandle(hAcceptServer);
    WaitForSingleObject(hGarbageCleaner, INFINITE);
    CloseHandle(hGarbageCleaner);
    WaitForSingleObject(hConsolePipe, INFINITE);
    CloseHandle(hConsolePipe);

    TerminateThread(hDispatchServer, 0);
    puts("shutdown dispatchServer");
    CloseHandle(hDispatchServer);
    TerminateThread(hResponseServer, 0);
    puts("shutdown responseServer");
    CloseHandle(hResponseServer);
    


    DeleteCriticalSection(&scListContact);
    FreeLibrary(st);

    return 0;
}
