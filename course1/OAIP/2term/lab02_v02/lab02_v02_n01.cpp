// 2 ������� 1 �������
#include <stdio.h>
#include <iostream>
int main()
{
    setlocale(LC_ALL, "");
    using namespace std;
    srand((unsigned)time(NULL));
    const int N = 100;
    int M1[N][N], M2[N][N], M3[N][N], columns, rows;
    errno_t errA, errB, errC; // errno_t ���������� � ��������������� ���������� ��� ������, ������� ��������� ��� ������ � ������
    FILE* fA, *fB, *fC; // ��������� fA �� ����

    errA = fopen_s(&fA, "fA.txt", "w"); // ���� ����������� ��� ������, � � "w"
    errB = fopen_s(&fB, "fB.txt", "w"); 
    errC = fopen_s(&fC, "f�.txt", "w"); 

    if ((errA != 0) || (errB != 0) || (errC != 0)) // ���� ����������� � ������ ����������� ��� ������ � ������ ������
    {
        perror("���������� ������� ����\n"); // �������������� errno � ������ � ������� ������ � ���������� � �������
        return EXIT_FAILURE; // ������ ��� ����������� ���� ��� ��������� ���������� � ����������
    }
    
    cout << "���������� ����� � ������ ������� = ";
    cin >> rows;
    cout << "���������� �������� � ������ ������� = ";
    cin >> columns;
    
    // ��������� � ������� � ������� ������ �������
    for (int i = 0; i < rows; i++)  
    {
        cout << "\n";
        for (int j = 0; j < columns; j++)
        {
            M1[i][j] = rand() % 10;
            cout << M1[i][j] << "\t";
        }
    }
    
    cout << "\n" << "\n";

    // ��������� � ������� � ������� ������ �������
    for (int i = 0; i < rows; i++)
    {
        cout << "\n";
        for (int j = 0; j < columns; j++)
        {
            M2[i][j] = rand() % 10;
            cout << M2[i][j] << "\t";
        }
    }

    cout << "\n" << "\n";

    // ������ ������� � ����� � �������
    for (int i = 0; i < rows; i++)
    {
        cout << "\n";
        for (int j = 0; j < columns; j++)
        {
            M3[i][j] = M1[i][j] + M2[i][j];
            cout << M3[i][j] << "\t";
        }
    }

    fprintf(fA, "%d", columns, "\n"); // ��������� ������� ����� = ���������� ��������
    fprintf(fB, "%d", columns, "\n");          
    fprintf(fC, "%d", columns, "\n");
   // ������ ������
    for (int i = 0; i < rows; i++)
    {
        fprintf(fA, "\n");
        fprintf(fB, "\n");
        fprintf(fC, "\n");
        for (int j = 0; j < columns; j++)
        {
            fprintf(fA, "%d\t ", M1[i][j]);
            fprintf(fB, "%d\t ", M2[i][j]);
            fprintf(fC, "%d\t ", M3[i][j]);
        }
    }

    // ����� �����������
    fclose(fA);
    fclose(fB);
    fclose(fC);

    return 0;
}
