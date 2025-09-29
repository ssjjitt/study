// 1. � ���������� �������, ��������� �� n ������������ ���������, ��������� ���������� ��������� �������, 
// ������ 0, � ����� ��������� �������, ������������ ����� ������������ ��������

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

    cout << "����� �����: " << endl;
    cin >> rows;
    cout << "����� ��������: " << endl;
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
    cout << "���������� �����: " << kolvo << endl;
    cout << "����������� �������: " << min << endl;
    cout << "������� � " << indexi << " ������" << endl;
    cout << "������� � " <<  indexj << " �������" << endl;

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
    cout << "�����: " << summa;

    for (int k = 0; k < rows; k++)
        delete[] massiv[k];
    delete[] massiv;

}