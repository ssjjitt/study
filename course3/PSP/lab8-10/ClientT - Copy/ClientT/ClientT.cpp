#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define SERVER_IP "127.0.0.1"  
#define SERVER_PORT 2000      
#define BUFFER_SIZE 50

void errorHandling(const char* msg) {
    cerr << msg << " Error code: " << WSAGetLastError() << endl;
    WSACleanup();
    exit(1);
}

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    int result;

    // Инициализация WinSock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        errorHandling("WSAStartup failed");
    }

    // Создание сокета
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        errorHandling("Socket creation failed");
    }

    // Настройка адреса сервера
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // Подключение к серверу
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        errorHandling("Connection to server failed");
    }

    cout << "Connected to server." << endl;

    string msg;
    cout << "Enter a service you want to test (Echo, Time, Random) \n";
    getline(cin, msg);

    result = send(clientSocket, msg.c_str(), msg.length() + 1, 0);
    if (result == SOCKET_ERROR) {
        errorHandling("Send failed");
    }


    if (msg == "Echo") {
        result = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (result > 0) {
            cout << "Server: " << buffer << endl;
        }

        while (true) {
            cout << "Enter a message (type 'exit' to quit): ";
            getline(cin, msg);
            
            result = send(clientSocket, msg.c_str(), msg.length() + 1, 0);
            if (result == SOCKET_ERROR) {
                errorHandling("Send failed");
            }

            if (msg == "exit") {
                result = send(clientSocket, "", strlen(""), 0);
                if (result == SOCKET_ERROR) {
                    errorHandling("Send failed");
                }
                break;
            }

            result = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if ((strcmp(buffer, "TimeOUT") == 0)) {
                cout << "connection is out of time" << endl;
                break;
            }
            else if (result > 0) {
                cout << "Echo from server: " << buffer << endl;
            }
            else if (result == 0) {
                cout << "Connection closed by server." << endl;
                break;
            }
            else {
                errorHandling("Recv failed");
            }
        }
    }
    else {
        result = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (result > 0) {
            cout << "Answer from server: " << buffer << endl;
        }
    }

    

    closesocket(clientSocket);
    WSACleanup();
    cout << "Disconnected from server." << endl;

    return 0;
}


//#define UNICODE 1
//#define _UNICODE 1
//
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>
//
//#define _SECOND 10000000
//
//typedef struct _MYDATA {
//    LPCTSTR szText;
//    DWORD dwValue;
//} MYDATA;
//
//VOID CALLBACK TimerAPCProc(
//    LPVOID lpArg,               // Data value
//    DWORD dwTimerLowValue,      // Timer low value
//    DWORD dwTimerHighValue)    // Timer high value
//
//{
//    // Formal parameters not used in this example.
//    UNREFERENCED_PARAMETER(dwTimerLowValue);
//    UNREFERENCED_PARAMETER(dwTimerHighValue);
//
//    MYDATA* pMyData = (MYDATA*)lpArg;
//
//    _tprintf(TEXT("Message: %s\nValue: %d\n\n"), pMyData->szText,
//        pMyData->dwValue);
//    MessageBeep(0);
//
//}
//
//int main(void)
//{
//    HANDLE          hTimer;
//    BOOL            bSuccess;
//    __int64         qwDueTime;
//    LARGE_INTEGER   liDueTime;
//    MYDATA          MyData;
//
//    MyData.szText = TEXT("This is my data");
//    MyData.dwValue = 100;
//
//    hTimer = CreateWaitableTimer(
//        NULL,                   // Default security attributes
//        FALSE,                  // Create auto-reset timer
//        TEXT("MyTimer"));       // Name of waitable timer
//    if (hTimer != NULL)
//    {
//        __try
//        {
//            // Create an integer that will be used to signal the timer 
//            // 5 seconds from now.
//            qwDueTime = -5 * 10000000;
//
//            // Copy the relative time into a LARGE_INTEGER.
//            liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
//            liDueTime.HighPart = (LONG)(qwDueTime >> 32);
//
//            bSuccess = SetWaitableTimer(
//                hTimer,           // Handle to the timer object
//                &liDueTime,       // When timer will become signaled
//                2000,             // Periodic timer interval of 2 seconds
//                TimerAPCProc,     // Completion routine
//                &MyData,          // Argument to the completion routine
//                FALSE);          // Do not restore a suspended system
//
//            if (bSuccess)
//            {
//                for (; MyData.dwValue < 1000; MyData.dwValue += 100)
//                {
//                    SleepEx(
//                        INFINITE,     // Wait forever
//                        TRUE);       // Put thread in an alertable state
//                }
//
//            }
//            else
//            {
//                printf("SetWaitableTimer failed with error %d\n", GetLastError());
//            }
//
//        }
//        __finally
//        {
//            CloseHandle(hTimer);
//        }
//    }
//    else
//    {
//        printf("CreateWaitableTimer failed with error %d\n", GetLastError());
//    }
//
//    return 0;
//}
