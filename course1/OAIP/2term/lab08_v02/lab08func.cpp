#include "head.h"

// создание очереди
void create(Number** begin, Number** end, int p) {      
    Number* t = new Number;     // выделение памяти
    t->next = NULL;
    if (*begin == NULL) 
        *begin = *end = t;
    else
    {
        t->info = p;    // заполнение поля
        (*end)->next = t;       // дальше
        *end = t;       
    }
}

// для вывода очереди
void view(Number* begin) 
{
    Number* t = begin;      // хранение дреса элемента
    if (t == NULL)      
    {
        cout << "пусто\n";
    }
    else {
        cout << "очередь:\n";
            while (t != NULL)       // пока очередь не пуста
            {
                cout << t->info << endl;    // выводим элемент
                t = t->next;            // и на следующий
            }   
        cout << '\n';
    }
}

// для удаления очереди
void del(Number* begin)
{
    Number* t = begin;      // хранение адреса элемента
    if (t == NULL)
    {
        cout << "пусто\n";
    }
    else
    {
        while (t != NULL)
        {
            t->info = NULL;     // устанавливаем в ноль
            t = t->next;            // и на следующий
        }
    }
    cout << "элементы удалены\n\n";
}

// узнать размер очереди
short sizeQ(Number* begin) 
{
    Number* t = begin;      // хранение адреса элемента
    short counter = 0, data = t->info;
    while (t != NULL)
    {
        if (data != NULL)
        {
            counter++;      // счетчик увеличивается
            t = t->next;    // перемещаемся дальше
        }
        else t = t->next;
    }
    cout << "размер очереди = " << counter << "\n\n";
    return counter;
}

// задание из варианта
Number* task(Number* begin) 
{
    Number* t = begin;
    int max = SHRT_MIN, min = SHRT_MAX;
    short couter = 1, data = t->info, pos1 = 0, pos2 = 0;
    while (t != NULL)
    {
        if (data != NULL)
        {
            if (t->info >= max) 
            {
                max = t->info;
                pos1 = couter;
            }
            if (t->info <= min)
            {
                min = t->info;
                pos2 = couter;
            }
            couter++;      // счетчик увеличивается
            t = t->next;    // перемещаемся дальше
        }
        else t = t->next;
    }
    cout << "max элемент: " << max << "\n";
    cout << "min элемент: " << min << "\n";
    cout << "Позиция max: " << pos1 << "\n";
    cout << "Позиция min: " << pos2 << "\n";
    cout << "Количество элементов между max и min: " << abs(pos1 - pos2) - 1 << "\n\n";
    return (t);
}
