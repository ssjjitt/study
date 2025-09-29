#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*SearchFuncIterative)(int*, int, int);
typedef int (*SearchFuncRecursive)(int*, int, int, int);
typedef const int* m_array;

FARPROC GetFunctionByIndex(HMODULE hLib, int funcIndex) {
    if (funcIndex == 1) {
        return GetProcAddress(hLib, (LPCSTR)(uintptr_t)1);
    }
    else if (funcIndex == 2) {
        return GetProcAddress(hLib, (LPCSTR)(uintptr_t)2);
    }
    return NULL;
}

m_array LoadArray(HMODULE hLib) {
    m_array arr = (m_array)GetProcAddress(hLib, "m_array");
    if (!arr) {
        arr = (m_array)GetProcAddress(hLib, (LPCSTR)(uintptr_t)3);
    }
    return arr;
}

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

    HMODULE hLib = LoadLibraryA(libName);
    if (!hLib) {
        printf("Zagruzaemaya biblioteka ne naydena!\n");
        return 1;
    }

    FARPROC rawFunc = NULL;

    if (atoi(funcName) != 0) {
        int funcIndex = atoi(funcName);
        rawFunc = GetFunctionByIndex(hLib, funcIndex);
        if (!rawFunc) {
            printf("Neizvestnyy nomer funkciyi: %d\n", funcIndex);
            FreeLibrary(hLib);
            return 1;
        }
    }
    else {
        rawFunc = GetProcAddress(hLib, funcName);
    }

    if (!rawFunc) {
        printf("Iskomaya funkciya %s ne naydena v biblioteke(GetProc) %s!\n", funcName, libName);
        FreeLibrary(hLib);
        return 1;
    }

    m_array arr = LoadArray(hLib);
    if (!arr) {
        printf("Array error!\n");
        FreeLibrary(hLib);
        return 1;
    }

    int number;
    if (argc < 4) {
        printf("Vvedite chislo dlya poiska: ");
        scanf("%d", &number);
    }
    else {
        number = atoi(argv[3]);
    }

    int index = -1;

    if ((strcmp(funcName, "binary_search_iterative") == 0) || (strcmp(funcName, "?binary_search_iterative@@YAHPEAHHH@Z") == 0) || (strcmp(funcName, "1") == 0)) {
        SearchFuncIterative searchFunc = (SearchFuncIterative)rawFunc;
        index = searchFunc(arr, 1024, number);
    }
    else if ((strcmp(funcName, "search") == 0) || (strcmp(funcName, "binary_search_recursive") == 0) || (strcmp(funcName, "2") == 0)) {
        SearchFuncRecursive searchFunc = (SearchFuncRecursive)rawFunc;
        index = searchFunc(arr, 0, 1023, number);
    }
    else {
        printf("Neizvestnaya func: %s\n", funcName);
        return 1;
    }

    if (index == -1) {
        printf("%s: Chislo ne naydeno!\n", funcName);
    }
    else {
        printf("%s: Chislo naydeno na pozitsii %d!\n", funcName, index);
    }

    FreeLibrary(hLib);
    return 0;
}
