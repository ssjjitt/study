// 14 вариант 1 задание
#include <iostream>
#include <stdio.h>
using namespace std;
#define N 100

int main()
{
    setlocale(LC_ALL, "rus");
    FILE* file1, * file2;
    int arr[N][N], size;
    errno_t err1, err2, err3;
    srand((unsigned)time(NULL));

    err1 = fopen_s(&file1, "file1.txt", "w");   // открываем файл
    if (err1 != 0)
    {
        perror("ошибка открытия file1.txt");        // при ошибке
        return EXIT_FAILURE;
    }

    cout << "количество строк/столбцов в матрице: " << endl;
    cin >> size;

    fprintf(file1, "%d \n", size);

    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < size; k++)
        {
            arr[i][k] = rand() % 10;            // создание массива, его вывод в консоль и запись в файл
            cout << arr[i][k] << '\t';
            fprintf(file1, "%d \t", arr[i][k]);
        }
        cout << '\n';
        fprintf(file1, "\n");
    }

    fclose(file1);//закроем файл для открытия в другом режиме
    err3 = fopen_s(&file1, "file1.txt", "r"); // открытие файла для считывания данных
    if (err3 != 0)
    {
        perror("ошибка открытия file1.txt");
        return EXIT_FAILURE;
    }
    err2 = fopen_s(&file2, "file2.txt", "w");
    if (err2 != 0)
    {
        perror("ошибка открытия file2.txt");
        return EXIT_FAILURE;
    }

    int x;
    fscanf_s(file1, "%d", &x); //узнаем размер массива, считывая файл
    int** arr1 = new int* [x]; 
    // инициализация динамического массива
    for (int i = 0; i < x; i++)
    {
        arr1[i] = new int[x];
    }

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            fscanf_s(file1, "%d", &(arr1[i][j]));   // читаем матрицу
        }

    }

    cout << "столбец для вывода" << endl;
    int k; 
    cin >> k;

    cout << endl << "столбец: " << endl;
    for (int i = 0; i < x; i++)
    {
        fprintf_s(file2, "%d\n", arr1[i][k]);       // записываем и выводим выбранный столбец
        printf("%d\n", arr1[i][k]);

    }

    fclose(file1); //закрытие всех файлов
    fclose(file2);

    delete[] arr1;  // освобождение памяти
    return 0;
}