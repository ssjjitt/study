#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Winsock2.h"
#include <thread>
#include <vector>
#pragma comment(lib, "WS2_32.lib")


using namespace std;

#define PATH "\\\\DESKTOP-2DSGURS\\meow\\file2.txt"

typedef void* HDFS;

// --------------------- Работа с критическими секциями через сервер ---------------------
struct CA {
    char ipaddr[15];
    char resurce[20];
    int clientnumber;
    enum Status { NOINIT, INIT, ENTER, LEAVE, WAIT } status;
    SOCKET socket;
    SOCKADDR_IN serverAddr;
};

string GetStatusText(CA::Status status) {
    switch (status) {
    case CA::NOINIT: return "NOINIT";
    case CA::INIT:   return "INIT";
    case CA::ENTER:  return "ENTER";
    case CA::LEAVE:  return "LEAVE";
    case CA::WAIT:   return "WAIT";
    default:         return "UNKNOWN";
    }
}

// Инициализация критической секции с подключением к серверу
CA InitCA(char ipaddr[15], char resurce[20], int number) {
    CA result;
    strcpy(result.ipaddr, ipaddr);
    strcpy(result.resurce, resurce);
    result.clientnumber = number;
    result.status = CA::NOINIT;

    // Инициализация сокетов
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
        throw runtime_error("WSAStartup failed");
    }

    result.socket = socket(AF_INET, SOCK_DGRAM, NULL);
    if (result.socket == INVALID_SOCKET) {
        throw runtime_error("Socket creation failed");
    }

    result.serverAddr.sin_family = AF_INET;
    result.serverAddr.sin_port = htons(2000);
    result.serverAddr.sin_addr.s_addr = inet_addr(result.ipaddr);

    // Отправляем команду на сервер об инициализации
    string message = "i " + string(result.resurce);
    int sentBytes = sendto(result.socket, message.c_str(), message.size(), 0,
        (sockaddr*)&result.serverAddr, sizeof(result.serverAddr));
    if (sentBytes == SOCKET_ERROR) {
        throw runtime_error("Failed to send init message");
    }

    result.status = CA::INIT;
    cout << "Section initialized: " << result.resurce << endl;

    return result;
}

// Вход в критическую секцию через сервер
bool EnterCA(CA& ca) {
    string message = "e " + string(ca.resurce);
    sendto(ca.socket, message.c_str(), message.size(), 0,
        (sockaddr*)&ca.serverAddr, sizeof(ca.serverAddr));

    char buffer[10];
    int serverAddrSize = sizeof(ca.serverAddr);
    int bytesReceived = recvfrom(ca.socket, buffer, sizeof(buffer), 0,
        (sockaddr*)&ca.serverAddr, &serverAddrSize);

    if (bytesReceived == SOCKET_ERROR) {
        cout << "Ошибка при получении ответа сервера" << endl;
        return false;
    }

    ca.status = CA::ENTER;
    cout << "Вход в секцию: " << ca.resurce << endl;
    return true;
}

// Выход из критической секции через сервер
bool LeaveCA(CA& ca) {
    string message = "l " + string(ca.resurce);
    sendto(ca.socket, message.c_str(), message.size(), 0,
        (sockaddr*)&ca.serverAddr, sizeof(ca.serverAddr));

    ca.status = CA::LEAVE;
    cout << "Выход из секции: " << ca.resurce << endl;
    return true;
}

// Закрытие секции через сервер
bool CloseCA(CA& ca) {
    string message = "c " + string(ca.resurce);
    sendto(ca.socket, message.c_str(), message.size(), 0,
        (sockaddr*)&ca.serverAddr, sizeof(ca.serverAddr));

    closesocket(ca.socket);
    WSACleanup();

    ca.status = CA::NOINIT;
    cout << "Закрытие секции: " << ca.resurce << endl;
    return true;
}

// --------------------- API DFS ---------------------
// Открытие файла
HDFS OpenDFSFile(const char* FileName) {
    fstream* file = new fstream();
    file->open(FileName, ios::in | ios::out | ios::app);
    if (!file->is_open()) {
        file->open(FileName, ios::out);
        file->close();
        file->open(FileName, ios::in | ios::out | ios::app);
    }

    if (file->is_open()) {
        cout << "Файл открыт: " << FileName << endl;
        return (HDFS)file;
    }
    cout << "Ошибка открытия файла: " << FileName << endl;
    delete file;
    return nullptr;
}

// Чтение из файла
int ReadDFSFile(HDFS hdfs, void* buf, int bufsize) {
    fstream* file = (fstream*)hdfs;
    file->read((char*)buf, bufsize);
    return file->gcount();
}

// Запись в файл
int WriteDFSFile(HDFS hdfs, void* buf, int bufsize) {
    fstream* file = (fstream*)hdfs;
    file->write((char*)buf, bufsize);
    return bufsize;
}

// Закрытие файла
void CloseDFSFile(HDFS hdfs) {
    fstream* file = (fstream*)hdfs;
    file->close();
    delete file;
}

void SimulateMultipleClients(CA& section, int numClients) {
    vector<thread> threads;

    // Функция для записи и чтения данных для одного клиента
    auto clientFunction = [&section](int clientId) {
        try {
            // Имитируем запись данных
            if (EnterCA(section)) {
                HDFS hdfs = OpenDFSFile(PATH);
                string data = "Client " + to_string(clientId) + " wrote data.\n";
                WriteDFSFile(hdfs, (void*)data.c_str(), data.size());
                CloseDFSFile(hdfs);
                LeaveCA(section);
                cout << "Client " << clientId << " wrote to file." << endl;
            }

            // Имитируем чтение данных
            if (EnterCA(section)) {
                HDFS hdfs = OpenDFSFile(PATH);
                char buffer[128] = { 0 };
                int bytesRead = ReadDFSFile(hdfs, buffer, sizeof(buffer));
                if (bytesRead > 0) {
                    cout << "Client " << clientId << " read: " << buffer << endl;
                }
                CloseDFSFile(hdfs);
                LeaveCA(section);
            }
        }
        catch (const exception& e) {
            cout << "Error for Client " << clientId << ": " << e.what() << endl;
        }
        };

    // Создаем несколько потоков для симуляции клиентов
    for (int i = 0; i < numClients; ++i) {
        threads.push_back(thread(clientFunction, i + 1));
    }

    // Ожидаем завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }
}

// --------------------- Основная функция ---------------------
int main() {
    setlocale(LC_ALL, "rus");

    CA section = InitCA((char*)"127.0.0.1", (char*)"D:\\meow\\file2.txt", 1);

    try {
        while (true) {
            cout << "\n1. Write to file\n2. Read from file\n3. Simulate Multiple Clients\n4. Exit\n";
            int choice;
            cin >> choice;
            if (choice == 1) {
                if (EnterCA(section)) {
                    HDFS hdfs = OpenDFSFile(PATH);
                    for (int i = 0; i < 10; ++i) {
                        time_t rawtime;
                        struct tm* timeinfo;
                        time(&rawtime);
                        timeinfo = localtime(&rawtime);
                        string data = "Client " + to_string(section.clientnumber) + " Line " + to_string(i + 1) + " Time:" + asctime(timeinfo) + "\n";
                        WriteDFSFile(hdfs, (void*)data.c_str(), data.size());
                    }
                    CloseDFSFile(hdfs);
                    LeaveCA(section);
                    cout << "\n10 строк успешно записано в файл." << endl;
                }
            }

            if (choice == 2) {
                cout << "\nВведите с какой строки читать:\n";
                int startLine;
                cin >> startLine;

                if (EnterCA(section)) {
                    HDFS hdfs = OpenDFSFile(PATH);
                    cout << "\nЧтение из файла, начиная с " << startLine << " строки:\n";

                    char buffer[128] = { 0 };  // Буфер для чтения данных
                    int bytesRead = 0;
                    int linesRead = 0;
                    int skippedLines = 0;  // Счётчик пропущенных строк

                    // Читаем данные до тех пор, пока не будет считано 10 строк
                    while (linesRead < 10 && (bytesRead = ReadDFSFile(hdfs, buffer, sizeof(buffer))) > 0) {
                        // Разбиваем данные на строки
                        string line;
                        for (int i = 0; i < bytesRead; ++i) {
                            if (buffer[i] == '\n') {  // Найден конец строки
                                skippedLines++;  // Пропускаем текущую строку

                                // Пропускаем строки до начала с заданной строки
                                if (skippedLines >= startLine) {
                                    cout << line << endl;  // Выводим строку
                                    linesRead++;  // Увеличиваем счётчик считанных строк
                                }
                                line.clear();  // Очищаем строку для следующего чтения
                            }
                            else {
                                line += buffer[i];  // Добавляем символ в строку
                            }

                            // Если прочитано 10 строк, выходим из цикла
                            if (linesRead >= 10) {
                                break;
                            }
                        }

                        // Если строка не пустая (не заканчивается на '\n'), выводим её
                        if (!line.empty() && skippedLines >= startLine) {
                            cout << line << endl;
                            linesRead++;
                        }
                    }

                    CloseDFSFile(hdfs);
                    LeaveCA(section);
                    cout << linesRead << " строк успешно считано из файла." << endl;
                }
            }

            if (choice == 3) {
                int numClients;
                cout << "Enter the number of clients to simulate: ";
                cin >> numClients;
                SimulateMultipleClients(section, numClients);
            }

            if (choice == 4) {
                CloseCA(section);
                break;
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        CloseCA(section);
    }

    return 0;
}
