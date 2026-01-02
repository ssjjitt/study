#include <iostream>
#include "Winsock2.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)
using namespace std;


#define INADDR_ANY        (u_long)0x00000000 //любой адрес       +++ 
#define INADDR_LOOPBACK    0x7f000001        // внутренняя петля +++
#define INADDR_BROADCAST  (u_long)0xffffffff // широковещание    +++  
#define INADDR_NONE        0xffffffff        // нет адреса  
#define ADDR_ANY           INADDR_ANY        // любой адрес       
#define BUFFER_SIZE 50
#define SERVER_PORT 2000

typedef struct sockaddr_in SOCKADDR_IN;    //                     +++
typedef struct sockaddr_in* PSOCKADDR_IN;
typedef struct sockaddr_in FAR* LPSOCKADDR_IN;

string GetErrorMsgText(int code)
{
    string msgText;
    switch (code) {
    case WSAEINTR:                 msgText = "Работа функции прервана";                           break;
    case WSAEACCES:                msgText = "Разрешение отвергнуто";                             break;
    case WSAEFAULT:                msgText = "Ошибочный адрес";                                   break;
    case WSAEINVAL:                msgText = "Ошибка в аргументе ";                               break;
    case WSAEMFILE:                msgText = "Слишком много файлов открыто";                      break;
    case WSAEWOULDBLOCK:           msgText = "Ресурс временно недоступен";                        break;
    case WSAEINPROGRESS:           msgText = "Операция в процессе развития";                      break;
    case WSAEALREADY:              msgText = "Операция уже выполняется ";                         break;
    case WSAENOTSOCK:              msgText = "Сокет задан неправильно   ";                        break;
    case WSAEDESTADDRREQ:          msgText = "Требуется адрес расположения ";                     break;
    case WSAEMSGSIZE:              msgText = "Сообщение слишком длинное ";                        break;
    case WSAEPROTOTYPE:            msgText = "Неправильный тип протокола для сокета ";            break;
    case WSAENOPROTOOPT:           msgText = "Ошибка в опции протокола";                          break;
    case WSAEPROTONOSUPPORT:       msgText = "Протокол не поддерживается ";                       break;
    case WSAESOCKTNOSUPPORT:       msgText = "Тип сокета не поддерживается ";                     break;
    case WSAEOPNOTSUPP:            msgText = "Операция не поддерживается ";                       break;
    case WSAEPFNOSUPPORT:          msgText = "Тип протоколов не поддерживается ";                 break;
    case WSAEAFNOSUPPORT:          msgText = "Тип адресов не поддерживается протоколом";          break;
    case WSAEADDRINUSE:            msgText = "Адрес уже используется ";                           break;
    case WSAEADDRNOTAVAIL:         msgText = "Запрошенный адрес не может быть использован";       break;
    case WSAENETDOWN:              msgText = "Сеть отключена ";                                   break;
    case WSAENETUNREACH:           msgText = "Сеть не достижима";                                 break;
    case WSAENETRESET:             msgText = "Сеть разорвала соединение";                         break;
    case WSAECONNABORTED:          msgText = "Программный отказ связи ";                          break;
    case WSAECONNRESET:            msgText = "Связь восстановлена ";                              break;
    case WSAENOBUFS:               msgText = "Не хватает памяти для буферов";                     break;
    case WSAEISCONN:               msgText = "Сокет уже подключен";                               break;
    case WSAENOTCONN:              msgText = "Сокет не подключен";                                break;
    case WSAESHUTDOWN:             msgText = "Нельзя выполнить send: сокет завершил работу";      break;
    case WSAETIMEDOUT:             msgText = "Закончился отведенный интервал  времени";           break;
    case WSAECONNREFUSED:          msgText = "Соединение отклонено  ";                            break;
    case WSAEHOSTDOWN:             msgText = "Хост в неработоспособном состоянии";                break;
    case WSAEHOSTUNREACH:          msgText = "Нет маршрута для хоста ";                           break;
    case WSAEPROCLIM:              msgText = "Слишком много процессов ";                          break;
    case WSASYSNOTREADY:           msgText = "Сеть не доступна ";                                 break;
    case WSAVERNOTSUPPORTED:       msgText = "Данная версия недоступна ";                         break;
    case WSANOTINITIALISED:        msgText = "Не выполнена инициализация WS2_32.DLL";             break;
    case WSAEDISCON:               msgText = "Выполняется отключение";                            break;
    case WSATYPE_NOT_FOUND:        msgText = "Класс не найден ";                                  break;
    case WSAHOST_NOT_FOUND:        msgText = "Хост не найден";                                    break;
    case WSATRY_AGAIN:             msgText = "Неавторизированный хост не найден";                 break;
    case WSANO_RECOVERY:           msgText = "Неопределенная  ошибка";                            break;
    case WSANO_DATA:               msgText = "Нет записи запрошенного типа";                      break;
    case WSA_INVALID_HANDLE:       msgText = "Указанный дескриптор события  с ошибкой";           break;
    case WSA_INVALID_PARAMETER:    msgText = "Один или более параметров с ошибкой";               break;
    case WSA_IO_INCOMPLETE:        msgText = "Объект ввода-вывода не в сигнальном состоянии";     break;
    case WSA_IO_PENDING:           msgText = "Операция завершится позже  ";                       break;
    case WSA_NOT_ENOUGH_MEMORY:    msgText = "Не достаточно памяти ";                             break;
    case WSA_OPERATION_ABORTED:    msgText = "Операция отвергнута ";                              break;
        //case WSAINVALIDPROCTABLE:      msgText = "Ошибочный сервис ";                                 break;
        //case WSAINVALIDPROVIDER:       msgText = "Ошибка в версии сервиса  ";                         break;
        //case WSAPROVIDERFAILEDINIT:    msgText = "Невозможно инициализировать сервис ";               break;
    case WSASYSCALLFAILURE:        msgText = "Аварийное завершение системного вызова ";           break;

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
    char* call, //[in] позывной сервера  
    short            port, //[in] номер порта сервера    
    struct sockaddr* from, //[out] указатель на SOCKADDR_IN
    int* flen  //[out] указатель на размер from 
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
    // устанавливаем атрибуты нового процесса
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    si.dwFlags = STARTF_USESTDHANDLES;

    // запускаем новый консольный процесс
    if (!CreateProcessA(
        NULL,    // имя процесса
        (LPSTR)"ClientRandom.exe",   // командная строка
        NULL,    // атрибуты защиты процесса по умолчанию
        NULL,    // атрибуты защиты первичного потока по умолчанию
        TRUE,    // наследуемые дескрипторы текущего процесса
        // наследуются новым процессом
        CREATE_NEW_CONSOLE,  // новая консоль  
        NULL,    // используем среду окружения процесса предка
        NULL,    // текущий диск и каталог, как и в процессе предке
        &si,     // вид главного окна - по умолчанию
        &pi      // здесь будут дескрипторы и идентификаторы
        // нового процесса и его первичного потока
    ))
    {
        cout << "Create process failed";
        return GetLastError();
    }
    lpHandles[0] = pi.hProcess;
    Sleep(100);

    STARTUPINFOA si2;
    PROCESS_INFORMATION pi2;
    // устанавливаем атрибуты нового процесса
    ZeroMemory(&si2, sizeof(STARTUPINFOA));
    si2.cb = sizeof(STARTUPINFOA);
    si2.dwFlags = STARTF_USESTDHANDLES;

    // запускаем новый консольный процесс
    if (!CreateProcessA(
        NULL,    // имя процесса
        (LPSTR)"ClientTime.exe",   // командная строка
        NULL,    // атрибуты защиты процесса по умолчанию
        NULL,    // атрибуты защиты первичного потока по умолчанию
        TRUE,    // наследуемые дескрипторы текущего процесса
        // наследуются новым процессом
        CREATE_NEW_CONSOLE,  // новая консоль  
        NULL,    // используем среду окружения процесса предка
        NULL,    // текущий диск и каталог, как и в процессе предке
        &si2,     // вид главного окна - по умолчанию
        &pi2      // здесь будут дескрипторы и идентификаторы
        // нового процесса и его первичного потока
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