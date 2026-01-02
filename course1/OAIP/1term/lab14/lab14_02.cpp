// ќпределить количество различных элементов матрицы размером nxm (повтор€ющиес€ элементы счи-тать один раз).
#include <iostream>
using namespace std;
int main()
{
    int rows, columns, kolvo = 0;

    cout << "rows: ";
    cin >> rows;
    cout << "columns: ";
    cin >> columns;

    char** arrchar = new char* [rows];
    for (int i = 0; i < rows; i++)
        arrchar[i] = new char[columns];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            cin >> arrchar[i][j];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (arrchar[0][0] != arrchar[i][j])
                kolvo++;
            else
                kolvo--;
        }

    }

    cout << "kolvo: " << kolvo;
}