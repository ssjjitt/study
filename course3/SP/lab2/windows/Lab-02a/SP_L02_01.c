#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#include <windows.h>
#include <stdio.h>
#define FILE_NAME "f.txt"
#define FILE_MAPPING_NAME L"FileMapping"
#define FILE_SIZE 65536 * 2
#define VIEW_OFFSET 65536
#define VIEW_SIZE 65536

void error_exit(const char* msg) {
	fprintf(stderr, "%s. Error code: %d\n", msg, GetLastError());
	exit(EXIT_FAILURE);
}

// заполнить файл
int main()
{
	FILE* fp = fopen(FILE_NAME, "w");
	if (!fp) error_exit("Failed to create file");
	for (int i = 0; i < FILE_SIZE; i++) {
		fputc('a', fp);
	}
	fclose(fp);

	HANDLE hFile = CreateFileA(
		FILE_NAME,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		error_exit("Failed to create or open file");

	printf("CreateFile done tap...\n");
	getchar();

	HANDLE hMapping = CreateFileMapping(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		FILE_SIZE,
		FILE_MAPPING_NAME);
	if (!hMapping)
		error_exit("Failed to create file mapping");

	printf("CreateFileMapping done tap...\n");
	getchar();

	LPVOID pViewRead = (int*)MapViewOfFile(
		hMapping,
		FILE_MAP_READ,
		0,
		VIEW_OFFSET,
		VIEW_SIZE);
	if (!pViewRead)
		error_exit("Failed to map file view for reading");
	printf("File content at offset %d:\n%.*s\n", VIEW_OFFSET, VIEW_SIZE, (char*)pViewRead);
	UnmapViewOfFile(pViewRead);

	printf("pViewRead done tap...\n");
	getchar();

	LPVOID pViewWrite2 = (int*)MapViewOfFile(
		hMapping,
		FILE_MAP_WRITE,
		0,
		VIEW_OFFSET,
		VIEW_SIZE);
	if (!pViewWrite2)
		error_exit("Failed to map file view for writing");

	printf("pViewWrite done tap...\n");
	getchar();

	memset(pViewWrite2, '\0', VIEW_SIZE);
	FlushViewOfFile(pViewWrite2, VIEW_SIZE);
	UnmapViewOfFile(pViewWrite2);

	printf("tap to close...");
	getchar();

	CloseHandle(hMapping);
	CloseHandle(hFile);
	system("notepad f");
	return 0;
}