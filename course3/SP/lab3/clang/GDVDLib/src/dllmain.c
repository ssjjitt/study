#include <windows.h>
#include <stdio.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason, LPVOID lpReserved) {
    FILE* log = fopen("D:\\univer\\!ÑÏ\\lab3\\dll_log.txt", "a");

    if (log) {
        switch (ul_reason) {
        case DLL_PROCESS_ATTACH:
            fprintf(log, "DLL_PROCESS_ATTACH\n");
            break;
        case DLL_THREAD_ATTACH:
            fprintf(log, "DLL_THREAD_ATTACH\n");
            break;

        case DLL_THREAD_DETACH:
            fprintf(log, "DLL_THREAD_DETACH\n");
            break;
        case DLL_PROCESS_DETACH:
            fprintf(log, "DLL_PROCESS_DETACH\n");
            break;
        }
        fclose(log);
    }
    return TRUE;
}
