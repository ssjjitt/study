#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_SIZE (512 * 1024 * 1024) // 512МиБ
#define VIEW_OFFSET (128 * 1024 * 1024)
#define VIEW_SIZE (128 * 1024 * 1024)

#define FILE_NAME L"2.txt"
#define FILE_MAPPING_NAME L"FileMapping"

void error_exit(const char* msg) {
    fprintf(stderr, "%s. Error code: %d\n", msg, GetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hFile = CreateFile(
        FILE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        error_exit("Failed to create or open file");
    }

    printf("CreateFile done tap...\n");
    getchar();

    HANDLE hMapping = CreateFileMapping(
        hFile,
        NULL,
        PAGE_READWRITE,
        0,
        FILE_SIZE,
        FILE_MAPPING_NAME
    );
    if (!hMapping) {
        error_exit("Failed to create file mapping");
    }

    printf("CreateFileMapping done tap...\n");
    getchar();

    LPVOID pViewRead = MapViewOfFile(
        hMapping,
        FILE_MAP_READ,
        0,
        VIEW_OFFSET,
        VIEW_SIZE
    );
    if (!pViewRead) {
        error_exit("Failed to map file view for reading");
    }

    printf("pViewRead done tap...\n");
    getchar();

    wprintf(L"File content at offset %d:\n%.*ls\n", VIEW_OFFSET, VIEW_SIZE, (wchar_t*)pViewRead);
    // исправить
    // %d - viewoffset
    // %.*ls - широкосимвольная строка
    UnmapViewOfFile(pViewRead);

    printf("tap to close...");
    getchar();

    CloseHandle(hMapping);
    CloseHandle(hFile);

    printf("Memory-mapped file operations completed successfully.\n");
    return 0;
}