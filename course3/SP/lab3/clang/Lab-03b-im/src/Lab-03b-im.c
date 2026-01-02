#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_search.h"  

__declspec(dllimport) int binary_search_iterative(int*, int, int);
__declspec(dllimport) int search(int*, int, int, int);
__declspec(dllimport) const int m_array[ARRAY_SIZE];  // Функция для получения массива из библиотеки

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Ne ukazana vyzyvaemaya funkciya!\n");
        return 1;
    }

    const char* funcName = argv[1];
    int number;

    if (!m_array) {
        printf("Array error!\n");
        return 1;
    }

    if (argc < 3) {
        printf("Vvedite chislo dlya poiska: ");
        scanf("%d", &number);
    }
    else {
        number = atoi(argv[2]);
    }

    int index = -1;
    if (strcmp(funcName, "binary_search_iterative") == 0) {
        index = binary_search_iterative(m_array, 1024, number);
    }
    else if ((strcmp(funcName, "search") == 0) || (strcmp(funcName, "?binary_search_recursive@@YAHQEAHHHH@Z") == 0)){
        index = search(m_array, 0, 1023, number);
    }

    if (index == -1)
        printf("%s: Zadannoe chislo ne naydeno!\n", funcName);
    else
        printf("%s: Chislo %d naydeno na pozitsii %d!\n", funcName, number, index);

    return 0;
}
