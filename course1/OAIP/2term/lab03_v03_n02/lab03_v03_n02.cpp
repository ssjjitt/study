// 3 вариант 2 задание
// Ввести с клавиатуры строку символов, состоящую из цифр и слов, разделенных пробелами, и записать ее в файл. Прочитать из файла данные, вывести слова строки и записать их в другой файл. 
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
    gets_s(str2, 256);
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
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] > '9' || string[i] < '0') {
            cout << string[i];
            f2 << string[i];
        }
    }
}

