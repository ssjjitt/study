#include <windows.h>
#include <stdio.h>

#define SHARED_MEMORY_NAME L"Mapping3"
#define MUTEX_NAME L"Lab-02-Mutex"
#define VIEW_SIZE (64 * 1024)    // 64 КБ
#define ITERATIONS 10

void error_exit(const char* msg) {
    fprintf(stderr, "Error: %s (code: %lu)\n", msg, GetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hMapping, hMutex;
    LPVOID pView;
    int* pData;

    hMutex = OpenMutex(SYNCHRONIZE, FALSE, MUTEX_NAME);
    if (!hMutex) error_exit("Failed to open mutex");

    printf("tap...\n");
    getchar();

    hMapping = OpenFileMapping(FILE_MAP_READ, FALSE, SHARED_MEMORY_NAME);
    if (hMapping == NULL) error_exit("Failed to open file mapping");

    printf("tap...\n");
    getchar();

    pView = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, VIEW_SIZE);
    if (!pView) error_exit("Failed to map view of file");

    pData = (int*)pView;

    for (int i = 0; i < ITERATIONS; i++) {
        WaitForSingleObject(hMutex, INFINITE);  // Ждём мьютекс

        printf("Reader: Read iteration %d\n", i);
        for (int j = 0; j < (VIEW_SIZE / sizeof(int)); j++) {
            printf("pData[%d] = %d\n", i, pData[j]);
        }


        printf("tap...\n");
        getchar();

        ReleaseMutex(hMutex);  // Освобождаем мьютекс
        Sleep(500);
    }

    printf("tap...\n");
    getchar();

    UnmapViewOfFile(pView);
    CloseHandle(hMapping);
    CloseHandle(hMutex);

    printf("tap to close...\n");
    getchar();

    return 0;
}