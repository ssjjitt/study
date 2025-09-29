// 2. Дана матрица. Переставляя ее строки и столбцы, добиться того, чтобы наибольший элемент оказался в верхнем левом углу.
#include <iostream>
int main()
{
    setlocale(LC_ALL, "Russian");
    using namespace std;
    srand((unsigned)time(NULL));
    
    const int n = 10;
    int **A;
    int rows, columns, max = -1, rowmax = 0, columnmax = 0;

    cout << "строки: " << endl;
    cin >> rows;
    cout << "колонки: " << endl;
    cin >> columns;

    A = new int* [rows];
    cout << "первоначальный массив: ";
    for (int i = 0; i < rows; i++)
    {
        A[i] = new int[rows];
        cout << endl;
        for (int j = 0; j < columns; j++)
        {
            A[i][j] = rand() % 20;
            cout << A[i][j] << " ";
            if (A[i][j] > max)
            {
                max = A[i][j];
                rowmax = i;
                columnmax = j;
            }
        }
    }

    cout << endl << endl;
    cout << "максимальный элемент = " << max << endl;
    cout << "находится в " << rowmax  << " строке" << endl;
    cout << "находится в " << columnmax << " столбце" << endl << endl;

    for (int i = 0; i < rows; i++)
    {
        
        for (int j = 0; j < columns; j++)
        {
            
            if (i == rowmax)
            {
                int tmp1 = A[0][j];
                int tmp2 = A[rowmax][j];

                A[0][j] = tmp2;
                A[rowmax][j] = tmp1; 

            }
        }
    }

    cout << "перемещаем строки: ";
    for (int i = 0; i < rows; i++)
    {
        cout << endl;
        for (int j = 0; j < columns; j++)
        { 
            cout << A[i][j] << " ";
        }
        
    }
    
    for (int i = 0; i < rows; i++)
    {
        
        for (int j = 0; j < columns; j++)
        {
            if (j == columnmax)
            {
                int tmp3 = A[i][0];
                int tmp4 = A[i][columnmax];

                A[i][0] = tmp4;
                A[i][columnmax] = tmp3;
            }

        }
    }

    cout << endl << endl <<  "перемещаем столбцы: ";
    for (int i = 0; i < rows; i++)
    {
        cout << endl;
        for (int j = 0; j < columns; j++)
        {
            cout << A[i][j] << " ";
        }

    }

    for (int k = 0; k < rows; k++) 
        delete[] A[k];
    delete[] A;
    return 0;
}

    
