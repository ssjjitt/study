#include <windows.h>
#include <fstream>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason, LPVOID lpReserved) {
    std::ofstream log("D:\\univer\\!ÑÏ\\lab3\\dll++_log.txt", std::ios::app);

    switch (ul_reason) {
    case DLL_PROCESS_ATTACH:
        log << "DLL_PROCESS_ATTACH\n"; break;
    case DLL_THREAD_ATTACH:
        log << "DLL_THREAD_ATTACH\n"; break;
    case DLL_THREAD_DETACH:
        log << "DLL_THREAD_DETACH\n"; break;
    case DLL_PROCESS_DETACH:
        log << "DLL_PROCESS_DETACH\n"; break;
    }

    return TRUE;
}
