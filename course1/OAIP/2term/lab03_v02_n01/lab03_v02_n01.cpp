//Скопировать в файл FILE2 только те строки из FILE1,  которые начинаются с буквы «А». 
//Подсчитать количество слов в FILE2.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");
    ifstream file1out("FILE1.txt");
    ofstream file2in("file2.txt");
    string buff;
    int count = 1;
    if (!file1out.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        while (getline(file1out, buff))
        {
            int len1 = buff.length();
            for (int i = len1 - 1; i < len1; i++)
            {
                if (buff[0] == 'A' || buff[0] == 'a')
                {
                    file2in << buff[i];
                }
                
            }file2in << '\n';

        }
        while (getline(file1out, buff))
        {
            int len1 = buff.length();
            for (int i = 1; i < len1; i++)
            {
                if (buff[0] == 'A' || buff[0] == 'a')
                {
                    if (buff[i] == ' ' || buff[i] == '\n' || buff[i] == '\0') count++;
                }

            }

        }

    }


    cout << count;
    file1out.close();
    file2in.close();


}