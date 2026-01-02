// 2. Дана целочисленная прямоугольная матрица. Определить количество столбцов, содержащих хотя бы один нулевой 
// элемент и номер строки, в которой находится самая длинная серия одинаковых элементов.

#include <iostream>
using namespace std;
int main() {
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "rus");
    const int x = 10, y = 10;
    int rows, columns, n, k = 0, **massiv;

    massiv = new int* [x];

    cout << "колво строк: " << endl;
    cin >> rows;
    cout << "колво столбцов: " << endl;
    cin >> columns;

    for (int i = 0; i < rows; i++)
    {
        massiv[i] = new int[x];
        cout << endl;
        for (int j = 0; j < columns; j++)

        {
            massiv[i][j] = rand() % 5;
            cout << massiv[i][j] << " ";
        }
    }

    for (int j = 0; j < columns; j++)
    {
        n = 0;
        for (int i = 0; i < rows; i++)
            if (massiv[i][j] != 0)
            {
                n++;
                if (n == rows)
                    k++;
            }
    }
    cout << endl << "количество столбцов с нулями: " << (columns - k);
 
    int kolvo = 1, max = 0, str = 0;


    for (int i = 0; i < rows; i++) 
    {
        
        for (int j = 0; j < columns; j++)
        {kolvo = 1;
            int tmp = massiv[i][j];
            if (massiv[i][j - 1] == tmp) 
            {
                kolvo++;
            }
        }
        if (kolvo > max)
        {
            max = kolvo;
            str = i;
        }
    }
    if (max > 0)
    {
        cout << endl << "максимальное количество подряд идущих: " << max;
        cout << endl << "строка: " << str;
    }
    else cout << endl << "максимальное количество подряд идущих: 1";
    for (int k = 0; k < rows; k++)
        delete[] massiv[k];
    delete[] massiv;

}