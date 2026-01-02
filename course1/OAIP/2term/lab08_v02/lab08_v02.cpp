// Создать очередь для целых чисел и функции для ввода, вывода и удаления элементов очереди. Найти количество элементов между максимальным и минимальным элементами очереди. 

#include<iostream> 
#include <windows.h>
#include "head.h"

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    Number* begin = NULL, * end, * t;
    t = new Number;
    short size, choose = NULL, p, sizeQueue;
    while (choose != 9)
    {
        cout << "Выберите, что сделать:\n"
             << "1 — ввод очереди\n"
             << "2 — вывод очереди\n" 
             << "3 — очистка очереди\n" 
             << "4 — определение размера очереди\n"
             << "5 — найти кол-во между max и min элементами\n"
             << "9 — выход из программы.\n";
        cin >> choose;
        cout << '\n';
        switch (choose)
        {
        case 1:
            cout << "Введите размер очереди:\n";
            cin >> size;
            cout << "Введите число: ";
            cin >> p;
            create(&begin, &end, p);
            t->info = p;
            t->next = NULL;
            begin = end = t;
            for (int i = 1; i < size; i++) //создание очереди
            {
                cout << "Введите число: ";
                cin >> p;
                create(&begin, &end, p);
            }
            cout << '\n';
            break;
        case 2:
            view(begin);
            break;
        case 3:
            del(begin);
            break;
        case 4:
            sizeQueue = sizeQ(begin);
            break;
        case 5:
            task(begin);
            break;
        case 9:
            exit(0);
        }
    }
}