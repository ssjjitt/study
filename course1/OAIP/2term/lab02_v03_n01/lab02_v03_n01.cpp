// 3 ������� 1 �������
#include <stdio.h>
#include <iostream>
int main()
{
    setlocale(LC_ALL, "");
    int a; errno_t err, columns = 4;
    FILE* f;
    err = fopen_s(&f, "matrix.txt", "w"); // ��������� ���� matrix.txt ��� ������
    if (err != 0)
    {
        perror("���������� ������� ����\n");    // � ������ ������ ��������
        return EXIT_FAILURE;
    }
    int Matrix[16] = { 2,7,12,-4,
                     6,-45,0,13,
                     96,43,-2,8,
                     33,-5,63,-11 };
    // ����� ������ �������
    fprintf(f, "%d �������\n", columns);    // ������� ���������� ��������
    for (int j = 0; j < 16; j += 4)
    {
        for (int i = j; i < j + 4; i++)
        {
            fprintf(f, "%d\t", Matrix[i]);  // ���������� � ���� matrix.txt �������������� �������
        }
        fprintf(f, "\n");
    }
    // ����� ������ �������
    err = fopen_s(&f, "matrixT.txt", "w"); // ��������� ���� matrixT.txt
    if (err != 0)
    {
        perror("���������� ������� ����\n");    // � ������ ������ ��������
        return EXIT_FAILURE;
    }
    fprintf(f, "%d �������.\n", columns);   // ������� ���������� ��������
    for (int j = 0; j < 4; j++)                     // ������ ������� ������� � ������, ����� ���������������
    {                                                   
        for (int i = j; i <= j + 12; i += 4)
        {
            fprintf(f, "%d\t", Matrix[i]);  // ���������� � ���� matrixT.txt ����������������� �������
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");

    printf("������ �������� � ���� matrixT.txt\n");
    fclose(f);  // ��������� ����
    return 0;
}