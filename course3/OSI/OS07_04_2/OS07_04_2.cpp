#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;


bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "rus");

    clock_t start = clock();
    int count = 0;
    int number = 2;

    cout << "Пронумерованный ряд простых чисел:\n";


    while (true) {
        int elapsedSeconds = (clock() - start) / CLOCKS_PER_SEC;

        if (isPrime(number)) {
            cout << count + 1 << ": " << number << ", Прошло: " << elapsedSeconds << " секунд\n";
            count++;
        }

        number++;

        if (elapsedSeconds == 120) {
            break;
        }
        Sleep(100);
    }
    Sleep(1000);
    cout << "Общее количество простых чисел: " << count << '\n';

}