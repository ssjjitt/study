// 2 вариант 1 задание
#include <stdio.h>
#include <iostream>
int main()
{
    setlocale(LC_ALL, "");
    using namespace std;
    srand((unsigned)time(NULL));
    const int N = 100;
    int M1[N][N], M2[N][N], M3[N][N], columns, rows;
    errno_t errA, errB, errC; // errno_t возвращает в соответствующей переменной код ошибки, которая возникает при работе с файлом
    FILE* fA, *fB, *fC; // указатель fA на файл

    errA = fopen_s(&fA, "fA.txt", "w"); // файл открывается для записи, т к "w"
    errB = fopen_s(&fB, "fB.txt", "w"); 
    errC = fopen_s(&fC, "fС.txt", "w"); 

    if ((errA != 0) || (errB != 0) || (errC != 0)) // блок выполняется в случае возникабщей при работе с файлом ошибки
    {
        perror("Невозможно создать файл\n"); // интерпретирует errno в строку и выводит вместе с сообщением в скобках
        return EXIT_FAILURE; // макрос для возвращения кода при неудачном выполнении и завершении
    }
    
    cout << "количество строк в первой матрице = ";
    cin >> rows;
    cout << "количество столбцов в первой матрице = ";
    cin >> columns;
    
    // заполняем и выводим в консоль первую матрицу
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

    // заполняем и выводим в консоль вторую матрицу
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

    // третья матрица и вывод в консоль
    for (int i = 0; i < rows; i++)
    {
        cout << "\n";
        for (int j = 0; j < columns; j++)
        {
            M3[i][j] = M1[i][j] + M2[i][j];
            cout << M3[i][j] << "\t";
        }
    }

    fprintf(fA, "%d", columns, "\n"); // начальный элемент файла = количеству столбцов
    fprintf(fB, "%d", columns, "\n");          
    fprintf(fC, "%d", columns, "\n");
   // запись матриц
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

    // файлы закрывабтся
    fclose(fA);
    fclose(fB);
    fclose(fC);

    return 0;
}
