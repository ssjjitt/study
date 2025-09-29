#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <chrono>
#include <thread>
#include <climits>
#include <iomanip>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "192.168.106.178"
#define SERVER_PORT 12345
#define REQUEST_INTERVAL 1 // Интервал запросов (10 секунд)
#define NUM_REQUESTS 10

struct GETSINCHRO	///запрос К на синхронизацию счетчика времени
{
    std::string cmd;		///всегда значение SINC
    int curvalue;	///тек. значение счетчика времени
};

uint64_t getOSTime() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count();
}

void runClient() {

    SYSTEMTIME tm;
    GETSINCHRO getsincro, setsincro;
    ZeroMemory(&setsincro, sizeof(setsincro));
    ZeroMemory(&getsincro, sizeof(getsincro));
    getsincro.cmd = "SINC";
    getsincro.curvalue = 0;

    std::cout << "Client run" << std::endl;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET clientSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "[ERROR] Socket creation failed: " << WSAGetLastError() << std::endl;
        return;
    }

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    int maxCorrection = 0;
    int minCorrection = INT_MAX;
    int totalCorrection = 0;
    int lensockaddr = sizeof(serverAddr);
    int maxcor = 0;
    int mincor = INT_MAX;
    int avgcorr = 0;
    uint64_t Cc = 0; // Инициализируем счетчик клиента нулем

    SOCKET ccS = socket(AF_INET, SOCK_DGRAM, 0);;

    for (int i = 0; i < NUM_REQUESTS; ++i) {
        GetSystemTime(&tm);
        sendto(ccS, (char*)&getsincro, sizeof(getsincro), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
        recvfrom(ccS, (char*)&setsincro, sizeof(setsincro), 0, (sockaddr*)&serverAddr, &lensockaddr);

        maxcor = (maxcor < setsincro.curvalue) ? setsincro.curvalue : maxcor;
        mincor = (mincor > setsincro.curvalue) ? setsincro.curvalue : mincor;
        avgcorr += setsincro.curvalue;

        std::cout << tm.wMonth << "." << tm.wDay << "." << tm.wYear << " - " << tm.wHour + 3 << ":" << tm.wMinute << ":" << tm.wSecond << "." << tm.wMilliseconds << "\n";
        std::cout << i + 1 << ") curvalue = " << getsincro.curvalue << " correction = " << setsincro.curvalue << " max corr/min corr: " << maxcor << "/" << mincor << "\n\n\n";

        if (i == 0)
            getsincro.curvalue += setsincro.curvalue;
        else
            getsincro.curvalue += setsincro.curvalue + 1000;




        char request[] = "sync";
        sendto(clientSock, request, sizeof(request), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        uint64_t Cs;
        socklen_t serverLen = sizeof(serverAddr);
        recvfrom(clientSock, (char*)&Cs, sizeof(Cs), 0, (struct sockaddr*)&serverAddr, &serverLen);

        std::cout << "----------------------------------\n";
        std::cout << "[CLIENT] Cs (server time): " << Cs << " ms\n";

        int correction = (Cs - Cc); // Исправлено: Cs - Cc

        // Обновляем статистику correction
        maxCorrection = max(maxCorrection, correction);
        minCorrection = min(minCorrection, correction);
        totalCorrection += correction;

        // Выводим данные
        uint64_t ostime = getOSTime();
        std::cout << "[CLIENT] OSTime: " << ostime << " ms\n"; // Добавлено: вывод счетчика клиента
        // std::cout << "[CLIENT] Correction: " << correction << " ms\n";
        //auto timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(ostime));
        //auto time_t_time = std::chrono::system_clock::to_time_t(timePoint);
        //std::cout << "[CLIENT] OStime (readable): " << std::put_time(std::localtime(&time_t_time), "%Y-%m-%d %H:%M:%S") << std::endl;
        std::cout << "[CLIENT] Cs - OSTime: " << ostime - Cs << " ms\n"; // Добавлено: вывод счетчика клиента
        std::cout << "----------------------------------\n";

        // Обновляем счетчик клиента
        Cc = Cc + correction + REQUEST_INTERVAL; // Исправлено: учитываем correction и Tc

        // Ждем 10 секунд перед следующим запросом
        std::this_thread::sleep_for(std::chrono::seconds(REQUEST_INTERVAL));
    }

    std::cout << "konechnaya\n";

    // Выводим среднее значение correction
    //std::cout << "Average correction: " << totalCorrection / NUM_REQUESTS << " ms\n";
    //std::cout << "Max correction: " << maxCorrection << " ms\n";
    //std::cout << "Min correction: " << minCorrection << " ms\n";

    closesocket(clientSock);
    WSACleanup();
}

int main() {
    runClient();
    getchar();
    return 0;
}