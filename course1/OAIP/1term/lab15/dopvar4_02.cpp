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
        for (int j = 0; j < columns; j++)
            massiv[i][j] = rand() % 5;
    }

    for (int i = 0; i < rows; i++)
    {
        cout << endl;
        for (int j = 0; j < columns; j++)
            cout << massiv[i][j] << " ";
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
    cout << endl << "количество столбцов без нулей: " << k;

    for (int k = 0; k < rows; k++) 
        delete[] massiv[k];
    delete[] massiv;

}