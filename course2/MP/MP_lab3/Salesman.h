#pragma once
#define INF   0x7fffffff
#include "Combi.h"
int salesman(              
    int n,         // [in]  колво городов
    const int* d,  // [in]  массив [n*n] расстояний 
    int* r         // [out] массив  [n] маршрут 0 x x x x
);