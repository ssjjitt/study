#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <chrono>
#include <thread>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define SERVER_IP "127.0.0.1"  // IP-адрес сервера
#define SERVER_PORT 2000       // Порт сервера
#define BUFFER_SIZE 50

void errorHandling(const char* msg) {
    cerr << msg << " Error code: " << WSAGetLastError() << endl;
    WSACleanup();
    exit(1);
}

void connectAndDisconnect() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    int result;

    // Инициализация WinSock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        errorHandling("WSAStartup failed");
    }

    // Настройка адреса сервера
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // Цикл подключения и отключения
    for (int i = 0; i < 5; ++i) {  // Например, повторить 5 раз
        // Создание сокета
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            errorHandling("Socket creation failed");
        }

        // Подключение к серверу
        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            errorHandling("Connection to server failed");
        }

        cout << "Connected to server (iteration " << i + 1 << ")." << endl;

        // Отправка сообщения на сервер
        string msg = "Time";
        result = send(clientSocket, msg.c_str(), msg.length() + 1, 0);
        if (result == SOCKET_ERROR) {
            errorHandling("Send failed");
        }

        // Получение ответа от сервера
        result = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (result > 0) {
            cout << "Server response: " << buffer << endl;
        }
        else if (result == 0) {
            cout << "Connection closed by server." << endl;
        }
        else {
            errorHandling("Receive failed");
        }

        // Закрытие соединения
        closesocket(clientSocket);
        cout << "Disconnected from server (iteration " << i + 1 << ")." << endl;

        // Пауза перед следующим подключением
        this_thread::sleep_for(chrono::seconds(2));  // 2 секунды ожидания
    }

    // Очистка WinSock
    WSACleanup();
}

int main() {
    connectAndDisconnect();
    return 0;
}
