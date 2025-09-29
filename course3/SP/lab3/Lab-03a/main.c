#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../GDVLib/binary_search.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Ne ykazana vizivaemaya func!\n");
        return 1;
    }

    const char* func_name = argv[1];
    int number;

    if (argc < 3) {
        printf("Vvedite chislo dlya poiska: ");
        scanf("%d", &number);
    }
    else {
        number = atoi(argv[2]);
    }

    int index = -1;

    if (strcmp(func_name, "binary_search_iterative") == 0) {
        index = binary_search_iterative(m_array, ARRAY_SIZE, number);
    }
    else if (strcmp(func_name, "binary_search_recursive") == 0) {
        index = binary_search_recursive(m_array, 0, ARRAY_SIZE - 1, number);
    }
    else {
        printf("Neizvestnaya func: %s\n", func_name);
        return 1;
    }

    if (index == -1) {
        printf("%s: Chislo ne naideno!\n", func_name);
    }
    else {
        printf("%s: Chislo %d naideno na positii %d!\n", func_name, number, index);
    }

    return 0;
}
