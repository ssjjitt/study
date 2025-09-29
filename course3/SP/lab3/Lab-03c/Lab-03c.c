#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define ARRAY_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Ne ukazana zagruzaemaya biblioteka!\n");
        return 1;
    }

    if (argc < 3) {
        printf("Ne ukazana vyzyvaemaya funkciya!\n");
        return 1;
    }

    const char* libName = argv[1];
    const char* funcName = argv[2];

    // Загружаем библиотеку
    void* handle = dlopen(libName, RTLD_LAZY);
    if (!handle) {
        printf("Zagruzaemaya biblioteka ne naydena: %s\n", dlerror());
        return 1;
    }

    // Загружаем функцию
    void* rawFunc = dlsym(handle, funcName);
    if (!rawFunc) {
        printf("Iskomaya funkciya ne naydena v biblioteke: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Преобразуем rawFunc в указатель на функцию
    int (*searchFunc)(int[], int, int) = (int (*)(int[], int, int)) rawFunc;

    int number = 0;
    if (argc < 4) {
        printf("Vvedite chislo dlya poiska: ");
        scanf("%d", &number);
    }
    else {
        number = atoi(argv[3]);
    }

    // Генерация массива
    int arr[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) arr[i] = i * 2;

    // Вызов функции поиска
    int result = searchFunc(arr, ARRAY_SIZE, number);

    if (result == -1) {
        printf("Chislo ne naydeno!\n");
    }
    else {
        printf("Chislo naydeno na pozitsii %d\n", result);
    }

    // Освобождаем ресурсы
    dlclose(handle);
    return 0;
}
