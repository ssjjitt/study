// 3 вариант 1 задание
#include <stdio.h>
#include <iostream>
int main()
{
    setlocale(LC_ALL, "");
    int a; errno_t err, columns = 4;
    FILE* f;
    err = fopen_s(&f, "matrix.txt", "w"); // открываем файл matrix.txt для записи
    if (err != 0)
    {
        perror("Невозможно создать файл\n");    // в случае ошибки открытия
        return EXIT_FAILURE;
    }
    int Matrix[16] = { 2,7,12,-4,
                     6,-45,0,13,
                     96,43,-2,8,
                     33,-5,63,-11 };
    // вывод первой матрицы
    fprintf(f, "%d столбца\n", columns);    // выводим количество столбцов
    for (int j = 0; j < 16; j += 4)
    {
        for (int i = j; i < j + 4; i++)
        {
            fprintf(f, "%d\t", Matrix[i]);  // записываем в файл matrix.txt первоначальную матрицу
        }
        fprintf(f, "\n");
    }
    // вывод второй матрицы
    err = fopen_s(&f, "matrixT.txt", "w"); // открываем файл matrixT.txt
    if (err != 0)
    {
        perror("Невозможно создать файл\n");    // в случае ошибки открытия
        return EXIT_FAILURE;
    }
    fprintf(f, "%d столбца.\n", columns);   // выводим количество столбцов
    for (int j = 0; j < 4; j++)                     // меняем местами столбцы и строки, чтобы транспонировать
    {                                                   
        for (int i = j; i <= j + 12; i += 4)
        {
            fprintf(f, "%d\t", Matrix[i]);  // записываем в файл matrixT.txt транспонированную матрицу
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");

    printf("Данные записаны в файл matrixT.txt\n");
    fclose(f);  // закрываем файл
    return 0;
}