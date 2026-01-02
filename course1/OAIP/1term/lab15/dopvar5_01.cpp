// 1. В одномерном массиве, состоящем из n вещественных элементов, вычислить количество элементов массива, 
// равных 0, и сумму элементов массива, расположённых после минимального элемента

#include <iostream>
using namespace std;
int main() {
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "rus");
    const int x = 10, y = 10;
    int rows, columns, indexi, indexj;
    int kolvo = 0, min = 100, summa = 0;
    int** massiv;

    massiv = new int* [x];

    cout << "колво строк: " << endl;
    cin >> rows;
    cout << "колво столбцов: " << endl;
    cin >> columns;

    for (int i = 0; i < rows; i++)
    {
        cout << endl;
        massiv[i] = new int[x];
        for (int j = 0; j < columns; j++)
        {
            massiv[i][j] = rand() % 19;
            cout << massiv[i][j] << " ";
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (massiv[i][j] == 0) 
                kolvo++;

            if (massiv[i][j] < min)
            {
                min = massiv[i][j];
                indexi = i;
                indexj = j;
            }
        }
    }
    cout << "количество нулей: " << kolvo << endl;
    cout << "минимальный элемент: " << min << endl;
    cout << "элемент в " << indexi << " строке" << endl;
    cout << "элемент в " <<  indexj << " колонке" << endl;

    for (int i = indexi; i < indexi + 1; i++)
    {
        cout << endl;
        for (int j = indexj + 1; j < columns; j++)
        {
            cout << massiv[i][j] << " ";
            summa += massiv[i][j];
        }
    }

    for (int i = indexi + 1; i < rows; i++)
    {
        cout << endl;
        for (int j = 0; j < columns; j++)
        {
            cout << massiv[i][j] << " ";
            summa += massiv[i][j];
        }
    }
    cout << "сумма: " << summa;

    for (int k = 0; k < rows; k++)
        delete[] massiv[k];
    delete[] massiv;

}