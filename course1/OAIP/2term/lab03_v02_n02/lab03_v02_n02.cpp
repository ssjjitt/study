// 2 вариант 2 задание
// Ввести с клавиатуры строку символов, состоящую из групп цифр и нулей, и записать ее в файл. Прочитать из файла данные и вывести самую короткую группу
#include <iostream>
#include <fstream>
using namespace std;
void inFile(fstream& f, char string[]); //Функция чтения из файла
void fromFile(fstream& f, ofstream& f2, char string[]); //Функция записи в файл

void main()
{
    setlocale(LC_ALL, "rus");
    ofstream ifile("FILE2.txt");
    fstream ofile("FILE1.txt");
	char str2[256];
    cout << "строка:  ";
    cin >> str2;
    inFile(ofile, str2);
    fromFile(ofile, ifile, str2);
}

void inFile(fstream& f, char string[256]) {
    for (int i = 0; i < strlen(string); i++)        // цикл для записи введенного с клавиатуры текста в файл
        f << string[i];
    f.close();      // закроем файл, чтобы потом он открылся для чтения
}

void fromFile(fstream& f, ofstream& f2, char string[256])
{
    
    
    cout << "строка из файла: ";
    for (int i = 0; i < strlen(string); i++)        // цикл для чтения символов из файла
    {
        f >> string[i];
        cout << string[i];
    }

    cout << endl;
    f.close();

    char* pstring = string;
    char ch, simvgrupp;
    int minkolvo = 0, kolvo = 256;
    ch = *pstring;

    do {                                            // ищем самую короткую группу символов
        pstring++;
        minkolvo++;
        if (ch != *pstring) {
            if (kolvo > minkolvo) {
                kolvo = minkolvo;
                simvgrupp = ch;
            }
            ch = *pstring;
            minkolvo = 0;
        }
    } while (*pstring != '\0');
    cout << "короткая группа: ";
    for (int i = 0; i < kolvo; i++)
    {
        cout << simvgrupp;
        f2 << simvgrupp;
    }
    f2.close();
}

