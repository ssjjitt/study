#include <iostream>
#include <ctime>

int main() {
    setlocale(LC_ALL, "rus");
    clock_t start = clock();
    int iterationCount = 0;
    bool flag5 = true, flag10 = true;

    while (true) {
        iterationCount++;

        if ((clock() - start) / CLOCKS_PER_SEC >= 5 && flag5) {
            std::cout << "После 5 секунд: " << iterationCount << std::endl;
            flag5 = false; 
        }

        if ((clock() - start) / CLOCKS_PER_SEC >= 10 && flag10) {
            std::cout << "После 10 секунд: " << iterationCount << std::endl;
            flag10 = false; 
        }

        if ((clock() - start) / CLOCKS_PER_SEC >= 15) {
            std::cout << "После 15 секунд: " << iterationCount << std::endl;
            break; 
        }

    }

    return 0;
}