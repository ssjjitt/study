// Создать список, содержащий символы. Найти символ, равный введенному с клавиатуры, вывести этот символ и предыдущий.
#include <iostream>
#include <fstream>
using namespace std;
struct list
{
    char symb;
    list* next;
};

// прототипы функций
void insert(list*&, char); //функция добавления элемента, передается адрес списка и символ, который добавляется 
float del(list*&, char);   //функция удаления, передается адрес списка и символ, который удаляется 
int IsEmpty(list*);         //функция, которая проверяет, пуст ли список
void printList(list*);      //функция вывода
void menu(void);     //функция, показывающая меню
void now_and_prev(list*);  //функция для поиска введенного и предыдущего символов
void toFile(list*& p);
void fromFile(list*& p);
void find(list*);

int main()
{
    setlocale(LC_CTYPE, "Russian");
    list* first = NULL;
    int choice = 0;
    char value;
    menu();    // вывести меню 
    while (choice != 8)
    {
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice)
        {
            //  кейс для добавления 
        case 1:  	cout << "Введите символ "; // добавить символ в список
            cin >> value;
            insert(first, value);
            break;
            // кейс для вывода листа
        case 2:
            printList(first);
            break;
            // кейс для удаления
        case 3:   if (!IsEmpty(first)) // проверка
        {
            cout << "Введите удаляемый символ ";
            cin >> value;
            if (del(first, value))
            {
                cout << "Удалено число " << value << endl;
                printList(first);
            }
            else
                cout << "Число не найдено" << endl;
        }
              else
            cout << "Список пуст" << endl;
            break;
            // кейс для суммы
        case 4:   now_and_prev(first);	// вычисление суммы	
            break;
            // кейс для записи в файл
        case 5: toFile(first);
            break;
            // кейс для чтения из файла
        case 6: fromFile(first);
            break;
            // кейс для поиска
        case 7: find(first);
            break;

        default:  cout << "Неправильный выбор" << endl;
            menu();
            break;
        }
    }
    cout << "Конец" << endl;
    return 0;
}

void menu(void)  //Вывод меню 
{
    cout << "Сделайте выбор:" << endl;
    cout << " 1 - Ввод" << endl;
    cout << " 2 - Вывод" << endl;
    cout << " 3 - Удаление" << endl;
    cout << " 4 - Вывод введенного и предыдущего" << endl;
    cout << " 5 - Запись в файл" << endl;
    cout << " 6 - Вывод из файла" << endl;
    cout << " 7 - Поиск элемента" << endl;
    cout << " 8 - Выход" << endl;
}
// -> доступ по указателю
void insert(list*& p, char value) //Добавление числа value в список 
{
    list* newP = new list;
    if (newP != NULL)     //есть ли место?  
    {
        newP->symb = value;       // присваиваем введенное в главной функции вещественное значение
        newP->next = p;
        p = newP;
    }
    else
        cout << "Операция добавления не выполнена" << endl;
}

float del(list*& p, char value)  // Удаление числа 
{
    list* previous, * current, * temp;
    if (value == p->symb)     //удаление предыдущего р, чтобы удалить первый р
    {
        temp = p;
        p = p->next;    // отсоединить узел 
        delete temp;      //освободить отсоединенный узел 
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->symb != value) // выполняется пока не найдем введенное значение(2 штуки перебрасываются последовательно)
        {
            previous = current;
            current = current->next; // перейти к следующему 
        }
        if (current != NULL)
        {
            temp = current;     // то, что будем удалять
            previous->next = current->next;     // переадресация
            free(temp); // удаление
            return value;
        }
    }
    return 0;
}

int IsEmpty(list* p) //Список  пустой? (1-да, 0-нет) 
{       // эту функцию можно сделать типа bool
    return p == NULL;
}

void printList(list* p)  //Вывод списка 
{
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        cout << "Список:" << endl;
        while (p != NULL)
        {
            cout << "\t" << p->symb;
            p = p->next;
        }
        cout << "\tNULL" << endl;
    }
}

void now_and_prev(list* p)  
{
    char element;
    bool isFind = false;
    cout << "Введите элемент" << endl;
    cin >> element;
    list* find = p;//с начала
    while (find)        // пока элементы списка не равны NULL
    {
        if (find->symb == element)        // если элемент совпадает с введенным
        {
            isFind = true;//нашли
            printf("Элемент найден\n");
            cout << "Текущий: " << p->next->symb << "\nПредыдущий: " << p->symb << "\n";
            break;
        }
        find = find->next;          // иначе перебираем значения
    }
    if (!isFind)
        printf("Элемент не найден\n");
}

void toFile(list*& p)
{
    list* temp = p;
    ofstream file1("text.txt");     // открываем файл для записи
    if (file1.fail())           // если файл не открыт
    {
        cout << "\n Ошибка открытия файла";
        exit(1);
    }
    while (temp)        // пока элемент списка не равен NULL
    {
        char nn = temp->symb;      // переменная для записи
        file1 << nn << "\n";        // записываем
        temp = temp->next;          // переходим на следующий
    }
    file1.close();      // закрываем файл
    cout << "Список записан в файл text.txt\n";
}

void fromFile(list*& p)
{
    char buf[10];       // буфер

    ifstream file1("text.txt");     // открываем файл для чтения

    if (file1.fail())           // если файл не открыт
    {
        cout << "\n Ошибка открытия файла";
        exit(1);
    }
    while (!file1.eof())        //пока не дочитали до конца файла
    {
        file1.getline(buf, 10);         //считываем строчку со значением
        if (strlen(buf))        //если длина > 0, то 
            insert(p, atoi(buf));       //добавляем в список
        cout << "\t" << buf;
    }
    cout << "\tNULL" << endl;
    file1.close();
}

void find(list* p)      // для поиска элементов
{
    bool isFind = false;
    char element;
    cout << "Введите элемент" << endl;
    cin >> element;
    list* find = p;//с начала
    while (find)        // пока элементы списка не равны NULL
    {
        if (find->symb == element)        // если элемент совпадает с введенным
        {
            isFind = true;//нашли
            printf("Элемент найден\n");
            break;
        }
        find = find->next;          // иначе перебираем значения
    }
    if (!isFind)
        printf("Элемент не найден\n");
}
