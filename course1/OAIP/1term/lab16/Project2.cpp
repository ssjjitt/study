#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
void main() {
    setlocale(LC_ALL, "rus");
    int i;
    char str[256];
    char c;
    
    
    cout << "Введите строку: " << endl;
    gets_s(str);
    cout << "Введите c: ";
    cin >> c;

    int length = strlen(str);

    for (i = 0; i < length; i++) {
        cout << *(str + i);
        if (*(str + i) == c) {
            cout << "*";
        }
    }
}