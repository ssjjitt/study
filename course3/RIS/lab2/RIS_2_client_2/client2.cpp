#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Winsock2.h"
#include <thread>
#include <vector>
#include <memory>
#include <sstream>

#pragma comment(lib, "WS2_32.lib")

using namespace std;

struct HDFS {
    std::fstream file;
};

int clnum = 1;

struct CA {
    char ipaddr[15];
    char resurce[20];
    int clientnumber;
    enum Status { 
        NOINIT, 
        INIT, 
        ENTER, 
        LEAVE, 
        WAIT 
    } status;
    SOCKET socket;
    SOCKADDR_IN serverAddr;
} section;

void InitSocket() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);
    section.socket = socket(AF_INET, SOCK_DGRAM, NULL);
    section.serverAddr.sin_family = AF_INET;
    section.serverAddr.sin_port = htons(2000);
    section.serverAddr.sin_addr.s_addr = inet_addr(section.ipaddr);
}

void InitCA(const char* ipaddr, const char* resurce, int number) {
    strncpy(section.ipaddr, ipaddr, sizeof(section.ipaddr) - 1);
    section.ipaddr[sizeof(section.ipaddr) - 1] = '\0';

    strncpy(section.resurce, resurce, sizeof(section.resurce) - 1);
    section.resurce[sizeof(section.resurce) - 1] = '\0';

    section.clientnumber = number;
    section.status = CA::NOINIT;

    InitSocket();

    section.status = CA::INIT;
}

void CloseCA() {
    closesocket(section.socket);
    WSACleanup();
    section.status = CA::NOINIT;
}

bool EnterCA() {
    char buffer[10];
    int serverAddrSize = sizeof(section.serverAddr);
    int bytesReceived = recvfrom(section.socket, buffer, sizeof(buffer), 0, (sockaddr*)&section.serverAddr, &serverAddrSize);

    if (bytesReceived == SOCKET_ERROR || strncmp(buffer, "WAIT", 4) == 0) {
        return false;
    }
    section.status = CA::ENTER;
    return true;
}

void LeaveCA() {
    section.status = CA::LEAVE;
}

HDFS OpenDFSFile(const char* FileName) {
    if (section.status == CA::INIT || section.status == CA::ENTER) {
        cout << "Клиент уже инициализирован в секции. Пропускаем повторную инициализацию." << endl;
    }
    else {
        InitCA("172.20.10.8", "Z:\\test.txt", clnum);
    }

    EnterCA();
    HDFS hdfs{};
    hdfs.file.open(FileName, ios::in | ios::out | ios::app);
    if (!hdfs.file.is_open()) {
        hdfs.file.open(FileName, ios::out);
        hdfs.file.close();
        hdfs.file.open(FileName, ios::in | ios::out | ios::app);
    }
    return hdfs;
}

int WriteDFSFile(HDFS& hdfs, void* buf, int bufsize) {
    if (!hdfs.file || !hdfs.file.is_open()) return -1;
    hdfs.file.write((char*)buf, bufsize);
    if (hdfs.file.fail()) {
        cerr << "Ошибка записи в файл (fstream error).\n";
        hdfs.file.clear(); 
        return -1;
    }
    hdfs.file.flush();
    LeaveCA();
    return bufsize;
}

int ReadDFSFile(HDFS& hdfs, void* buf, int bufsize) {
    if (!hdfs.file || !hdfs.file.is_open() || !buf || bufsize <= 0)
        return -1;
    hdfs.file.read((char*)buf, bufsize);
    int bytesRead = static_cast<int>(hdfs.file.gcount());
    if (hdfs.file.eof()) {
        return 0;  
    }
    LeaveCA();
    return bytesRead > 0 ? bytesRead : -1;
}

void CloseDFSFile(HDFS& hdfs) {
    hdfs.file.close();
    CloseCA();
}
int main() {
    setlocale(LC_ALL, "rus");

    HDFS hdfs = OpenDFSFile("Z:\\test.txt"); 

    string initMsg = "i " + string(section.resurce);
    sendto(section.socket, initMsg.c_str(), initMsg.size(), 0, (sockaddr*)&section.serverAddr, sizeof(section.serverAddr));
    cout << "Инициализация отправлена.\n";

    while (true) {
        cout << "\n1. Write to file\n2. Read from file\n3. Exit\n";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string enterMsg = "e " + string(section.resurce);
            if (sendto(section.socket, enterMsg.c_str(), enterMsg.size(), 0, (sockaddr*)&section.serverAddr, sizeof(section.serverAddr)) == SOCKET_ERROR) {
                cerr << "Ошибка отправки сообщения входа.\n";
                continue;
            }
            cout << "Запрос на вход отправлен.\n";
            cout << "Вход в секцию разрешён.\n";
            for (int i = 0; i < 10; ++i) {
                time_t rawtime;
                struct tm* timeinfo;
                time(&rawtime);
                timeinfo = localtime(&rawtime);

                string data = "Client " + to_string(clnum) +
                    " Line " + to_string(i + 1) +
                    " Time: " + asctime(timeinfo);
                cout << data << endl;
                if (WriteDFSFile(hdfs, (void*)data.c_str(), data.size()) == -1) {
                    cerr << "Ошибка записи в файл.\n";
                    break;
                }
            }
            cout << "\n10 строк успешно записано в файл." << endl;
            string leaveMsg = "l " + string(section.resurce);
            sendto(section.socket, leaveMsg.c_str(), leaveMsg.size(), 0, (sockaddr*)&section.serverAddr, sizeof(section.serverAddr));
            cout << "Клиент покинул секцию.\n";
        }

        if (choice == 2) {
            string enterMsg = "e " + string(section.resurce);
            if (sendto(section.socket, enterMsg.c_str(), enterMsg.size(), 0, (sockaddr*)&section.serverAddr, sizeof(section.serverAddr)) == SOCKET_ERROR) {
                cerr << "Ошибка отправки сообщения входа.\n";
                continue;
            }
            cout << "Запрос на вход отправлен.\n";
            cout << "Вход в секцию разрешён.\n";

            cout << "\nВведите с какой строки читать:\n";
            int startLine;
            cin >> startLine;
            cin.ignore(); 

            cout << "\nЧтение 10 строк начиная со строки " << startLine << ":\n";

            hdfs.file.seekg(0, ios::beg); 
            string line;
            int currentLine = 1;
            int linesRead = 0;

            while (getline(hdfs.file, line) && linesRead < 10) {
                if (currentLine >= startLine) {
                    cout << line << endl;
                    linesRead++;
                }
                currentLine++;
            }

            string leaveMsg = "l " + string(section.resurce);
            sendto(section.socket, leaveMsg.c_str(), leaveMsg.size(), 0, (sockaddr*)&section.serverAddr, sizeof(section.serverAddr));
            cout << "Клиент покинул секцию.\n";
        }

        if (choice == 3) {
            string closeMsg = "c " + string(section.resurce);
            sendto(section.socket, closeMsg.c_str(), closeMsg.size(), 0, (sockaddr*)&section.serverAddr, sizeof(section.serverAddr));
            cout << "Закрытие сессии.\n";
            CloseDFSFile(hdfs);
            break;
        }
    }
    CloseDFSFile(hdfs);
    return 0;
}