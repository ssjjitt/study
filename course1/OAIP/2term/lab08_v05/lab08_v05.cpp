// Создать очередь для символов и функции для ввода, вывода и удаления элементов очереди. 
// Ввести символы с клавиатуры в очередь. После введения 5-го символа в ответ на каждый вводимый удалять по одному элементу из очереди. 
#include<iostream> 
#include <windows.h>
#include "Header.h"

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    Number* begin = NULL, * end, * t;
    t = new Number;
    short size = 6, choose = NULL, p, sizeQueue;
    while (choose != 9)
    {
        cout << "Выберите, что сделать:\n"
            << "1 — ввод очереди\n"
            << "2 — вывод очереди\n"
            << "3 — очистка очереди\n"
            << "9 — выход из программы.\n";
        cin >> choose;
        cout << '\n';
        switch (choose)
        {
        case 1:
            cout << "Введите число: ";
            cin >> p;
            create(&begin, &end, p);
            t->info = p;
            t->next = NULL;
            begin = end = t;
            for (int i = 1; i < size; i++) //создание очереди
            {
                if (i >= 5) {
                    delEl(begin);
                }
                cout << "Введите число: ";
                cin >> p;
                create(&begin, &end, p);
            }
            view(begin);
            cout << '\n';
            break;
        case 2:
            view(begin);
            break;
        case 3:
            del(begin);
            break;
        case 9:
            exit(0);
        }
    }
}