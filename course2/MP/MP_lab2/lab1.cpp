// Main      
#include <stdio.h>
#include <iostream>
#include <iomanip> 
#include "Combi.h"
#include "knapsack.h"
#include <ctime>
#define N (sizeof(AA)/2)
#define M 3
#define NN 18
using namespace std;

int main()
{
    // Задание 1.  Разобрать и разработать генератор подмножеств заданного множества. 
    setlocale(LC_ALL, "rus");
    char  AA[][2] = { "A", "B", "C", "D" };
    cout << endl << " - ГЕНЕРАТОР МНОЖЕСТВА ВСЕХ ПОДМНОЖЕСТВ -" << endl << "Исходное множество: " << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    cout << "}" << endl << "Генерация всех подмножеств  ";
    combi::subset s1(sizeof(AA) / 2);         // создание генератора   
    int  n = s1.getfirst();                // первое (пустое) подмножество    
    while (n >= 0)                          // пока есть подмножества 
    {
        cout << endl << "{ ";
        for (int i = 0; i < n; i++)
            cout << AA[s1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        cout << "}";
        n = s1.getnext();                   // cледующее подмножество 
    };
    cout << endl << "всего: " << s1.count() << endl;



    // Задание 2.  Разобрать и разработать генератор сочетаний. 
    cout << endl << " --- ГЕНЕРАТОР СОЧЕТАНИЙ ---" << endl << "Исходное множество: " << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    cout << "}" << endl << "Генерация сочетаний ";
    combi::xcombination xc(sizeof(AA) / 2, 3);
    cout << "из " << xc.n << " по " << xc.m;
    int  n1 = xc.getfirst();
    while (n1 >= 0)
    {
        cout << endl << xc.nc << ": { ";
        for (int i = 0; i < n1; i++)
            cout << AA[xc.ntx(i)] << ((i < n1 - 1) ? ", " : " ");
        cout << "}";
        n1 = xc.getnext();
    };
    cout << endl << "всего: " << xc.count() << endl;



    // Задание 3.  Разобрать и разработать генератор перестановок.
    cout << endl << " --- ГЕНЕРАТОР ПЕРЕСТАНОВОК ---" << endl << "Исходное множество: " << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    cout << "}" << endl << "Генерация перестановок ";
    combi::permutation p(sizeof(AA) / 2);
    __int64  n2 = p.getfirst();
    while (n2 >= 0)
    {
        cout << endl << setw(4) << p.np << ": { ";
        for (int i = 0; i < p.n; i++)
            cout << AA[p.ntx(i)] << ((i < p.n - 1) ? ", " : " ");
        cout << "}";
        n2 = p.getnext();
    };
    cout << endl << "всего: " << p.count() << endl;



    // Задание 4.  Разобрать и разработать генератор размещений
    cout << endl << " --- ГЕНЕРАТОР РАЗМЕЩЕНИЙ ---" << endl << "Исходное множество: " << "{ ";
    for (int i = 0; i < N; i++)
        cout << AA[i] << ((i < N - 1) ? ", " : " ");
    cout << "}" << endl << "Генерация размещений  из  " << N << " по " << M;
    combi::accomodation s(N, M);
    int  n3 = s.getfirst();
    while (n3 >= 0)
    {
        cout << endl << setw(2) << s.na << ": { ";
        for (int i = 0; i < 3; i++)
            cout << AA[s.ntx(i)] << ((i < n3 - 1) ? ", " : " ");
        cout << "}";
        n3 = s.getnext();
    };
    cout << endl << "всего: " << s.count() << endl;


    // Задание 5. Рюкзак
    int V = 300,                // вместимость рюкзака              
        v[] = { 10, 15, 5, 95, 35, 40, 145, 20, 210, 15, 100, 35, 10, 25, 230, 100, 150, 170 },     // размер предмета каждого типа  
        c[] = { 10, 25, 30, 45, 50, 40, 25, 10, 20, 30, 55, 5, 45, 50, 10, 20, 25, 5 };     // стоимость предмета каждого типа 
    short m[NN];                // количество предметов каждого типа  {0,1}   
    int maxcc = knapsack_s(
        V,   // [in]  вместимость рюкзака 
        NN,  // [in]  количество типов предметов 
        v,   // [in]  размер предмета каждого типа  
        c,   // [in]  стоимость предмета каждого типа     
        m    // [out] количество предметов каждого типа  
    );
   
    clock_t t1, t2;
    t1 = clock();
    cout << endl << "-------- Задача о рюкзаке --------- " << endl << "- количество предметов : " << NN << endl << "- вместимость рюкзака  : " << V << endl << "- размеры предметов    : ";
    for (int i = 0; i < NN; i++) 
        cout << v[i] << " ";
    cout << endl << "- стоимости предметов  : ";
    for (int i = 0; i < NN; i++)  
        cout << v[i] * c[i] << " ";
    cout << endl << "- оптимальная стоимость рюкзака: " << maxcc << endl << "- вес рюкзака: ";
    int sb = 0;
    for (int i = 0; i < NN; i++)
        sb += m[i] * v[i];
    cout << sb << endl << "- выбраны предметы: ";
    for (int i = 0; i < NN; i++)  
        cout << " " << m[i] << "(вес: " << v[i] * c[i] << ")";
    t2 = clock();
    cout << endl << endl;
    cout << "время: " << t2 - t1 << endl;
  system("pause");
    return 0;
}
// 12 - 14
// 13 - 15
// 14 - 16
// 15 - 16
// 16 - 17
// 17 - 19
// 18 - 21
// 19 - 21
// 20 - 23