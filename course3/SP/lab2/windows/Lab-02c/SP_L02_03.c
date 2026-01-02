#include <stdio.h>
#include <windows.h>
#define SHARED_MEMORY_NAME L"Mapping3"
#define MUTEX_NAME L"Lab-02-Mutex"
#define TOTAL_SIZE (640 * 1024)  // 640 КБ
#define VIEW_SIZE (64 * 1024)    // 64 КБ
#define ITERATIONS 10 // 64 * 10 = 640 кб для записи

void error_exit(const char* msg) {
    fprintf(stderr, "Error: %s (code: %lu)\n", msg, GetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hMapping, hMutex;
    LPVOID pView;
    int* pData;

    hMutex = CreateMutex(
        NULL, 
        FALSE, 
        MUTEX_NAME);
    if (!hMutex) error_exit("Failed to create mutex");

    printf("tap...\n");
    getchar();

    hMapping = CreateFileMapping(
        INVALID_HANDLE_VALUE, 
        NULL, 
        PAGE_READWRITE, 
        0, 
        TOTAL_SIZE, 
        SHARED_MEMORY_NAME);

    if (hMapping == NULL) error_exit("Failed to create file mapping");

    printf("tap...\n");
    getchar();

    pView = MapViewOfFile(
        hMapping, 
        FILE_MAP_WRITE, 
        0, 
        0, 
        VIEW_SIZE);
    if (!pView) error_exit("Failed to map view of file");

    pData = (int*)pView;

    for (int i = 0; i < ITERATIONS; i++) {
        WaitForSingleObject(hMutex, INFINITE); 

        printf("Writer: Wrote iteration %d\n", i);
        for (int j = 0; j < (VIEW_SIZE / sizeof(int)); j++) {
            pData[j] = i * 1000 + j;  
            printf("pData[%d] = %d\n", i, pData[j]);
        }

        printf("tap...\n");
        getchar();

        ReleaseMutex(hMutex); 
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