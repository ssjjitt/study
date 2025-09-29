#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
# define str_len 40                               
# define SIZE 40 

using namespace std;

struct Initial {
    char fio[str_len];
    char telephone[str_len];
    char email[str_len];
    char product[str_len];
    int numProduct;
    char dateSale[str_len];
    char dateDelivery[str_len];
};

vector<Initial> initial;
struct Initial bad;

void ReadingData(string fileName)
{
    cout << "=======================================\n";
    for (auto client : initial)
    {
        cout << "Фамилия клиента: " << client.fio << "\n";
        cout << "Почта клиента: " << client.email << "\n";
        cout << "Телефон клиента: " << client.telephone << "\n";
        cout << "Купленный товар: " << client.product << "\n";
        cout << "Количество товаров: " << client.numProduct << "\n";
        cout << "Дата продажи: " << client.dateSale << "\n";
        cout << "Дата доставки: " << client.dateDelivery << "\n";
        cout << "=======================================\n";
        
    }
}

void ReadFromFile(string fileName) {
    ifstream read(fileName, ios::app);
    if (read) {
        while (!read.eof())
        {
            Initial temp;
            read >> temp.fio;
            read >> temp.email;
            read >> temp.telephone;
            read >> temp.product;
            read >> temp.numProduct;
            read >> temp.dateSale;
            read >> temp.dateDelivery;
            initial.push_back(temp);
        }
    }
    else
        cout << "Ошибка открытия файла!" << endl;
    read.close();
}

void WriteInFile(string fileName) {

    ofstream record(fileName, ios::app);
    if (record) {
        for (auto client : initial)
        {
            record << client.fio << "\n";
            record << client.email << "\n";
            record << client.telephone << "\n";
            record << client.product << "\n";
            record << client.numProduct << "\n";
            record << client.dateSale << "\n";
            record << client.dateDelivery << "\n";
        }
    }
    else
        cout << "Ошибка открытия файла!" << endl;
    record.close();
}
void SavingData(string fileName)
{
    ofstream record(fileName, ios::app);
    if (record) {
        cout << "Ввод информации" << endl;
        Initial list_of_clients;
        cout << endl << "Фамилия клиента: " << endl;
        cin >> list_of_clients.fio;
        cout << "Номер телефона: " << endl;
        cin >> list_of_clients.telephone;
        cout << "Электронная почта: " << endl;
        cin >> list_of_clients.email;
        cout << "Товар: " << endl;
        cin >> list_of_clients.product;
        cout << "Количество товаров: " << endl;
        cin >> list_of_clients.numProduct;
        cout << "Дата продажи: " << endl;
        cin >> list_of_clients.dateSale;
        cout << "Дата доставки: " << endl;
        cin >> list_of_clients.dateDelivery;
        initial.push_back(list_of_clients);


    }
    else
        cout << "Ошибка открытия файла!" << endl;
    record.close();
}

void Change()
{
    int ind;
    cout << "Input index for changing\n";
    cin >> ind;
    cout << endl << "Фамилия клиента: " << endl;
    cin >> initial[ind].fio;
    cout << "Номер телефона: " << endl;
    cin >> initial[ind].telephone;
    cout << "Электронная почта: " << endl;
    cin >> initial[ind].email;
    cout << "Товар: " << endl;
    cin >> initial[ind].product;
    cout << "Количество товаров: " << endl;
    cin >> initial[ind].numProduct;
    cout << "Дата продажи: " << endl;
    cin >> initial[ind].dateSale;
    cout << "Дата доставки: " << endl;
    cin >> initial[ind].dateDelivery;
}

void delInFile(string fileName) {
    ofstream file("Output.txt", ios_base::trunc);

}

void DeleteData()
{
    int d;
    cout << "\n 1 - Удалить определённый фрагмент\n 2 - Удалить всё  ";
    cin >> d;
    auto iter = initial.cbegin();
    switch (d)
    {
    case 1:
        int ind;
        cout << "Выберете фрагмент от 0 до " << initial.size() << "\n";
        cin >> ind;
        initial.erase(ind + iter);
        break;
    case 2:
        initial.clear();
        break;
    default:

        break;
    }


}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, ".1251");
    int filevar = NULL, var = NULL;
    string fileName;
    do {
        cout << "ФАЙЛ: \n 1-ваше имя файла\n 2-по стандарту\n 0 - выход\n";
        cin >> filevar;
        switch (filevar)
        {
        case 1:
        {
            cout << "введите ваше имя файла\n";
            cin >> fileName;
            do {
                cout << "\n1-вывод в консоль" << endl;
                cout << "2-для ввода новой записи" << endl;
                cout << "3-запись в файл" << endl;
                cout << "4-чтение из файла" << endl;
                cout << "5-удаление всего содержимого файла" << endl;
                cout << "6-частичное удаление информации" << endl;
                cout << "7-изменение информации" << endl;
                cout << "0-для выхода" << endl;
                cin >> var;
                switch (var)
                {
                case 1: ReadingData(fileName); break;
                case 2: SavingData(fileName); break;
                case 3: WriteInFile(fileName); break;
                case 4: ReadFromFile(fileName); break;
                case 5: delInFile(fileName); break;
                case 6: DeleteData(); break;
                case 7: Change(); break;
                default:
                    break;
                }
            } while (var != 0);
        }
        case 2:
        {
            do
            {
                cout << "\n1-вывод в консоль" << endl;
                cout << "2-для ввода новой записи" << endl;
                cout << "3-запись в файл" << endl;
                cout << "4-чтение из файла" << endl;
                cout << "5-удаление всего содержимого файла" << endl;
                cout << "6-частичное удаление информации" << endl;
                cout << "7-изменение информации" << endl;
                cout << "0-для выхода" << endl;
                cin >> var;
                switch (var)
                {
                case 1: ReadingData("Output.txt"); break;
                case 2: SavingData("Output.txt"); break;
                case 3: WriteInFile("Output.txt"); break;
                case 4: ReadFromFile("Output.txt"); break;
                case 5: delInFile("Output.txt"); break;
                case 6: DeleteData(); break;
                case 7: Change(); break;
                default:
                    break;
                }
            } while (var != 0);
        }
        default:
            break;
        }
    } while (filevar != 0);
}
