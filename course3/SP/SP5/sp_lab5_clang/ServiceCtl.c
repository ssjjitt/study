#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printError(const char* functionName);
const char* getStateString(DWORD dwCurrentState);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ServiceCtl <ServiceName> <Operation> [Optional Arguments]\n");
        fprintf(stderr, "Operations: Create <Path>, Delete, Start, Stop, Pause, Continue, Info, Test <Code>\n");
        return 1;
    }

    const char* serviceName = argv[1];
    const char* operation = argv[2];
    const char* optionalArg1 = (argc > 3) ? argv[3] : NULL;

    printf("Service: %s, Operation: %s\n", serviceName, operation);
    if (optionalArg1) printf("Optional Arg: %s\n", optionalArg1);

    // Подключение к SCM
    SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (scManager == NULL) {
        printError("OpenSCManager");
        fprintf(stderr, "Error: Could not connect to SCM. Run as Administrator?\n");
        return 1;
    }

    SC_HANDLE hService = NULL;

    // Обработка операций
    BOOL success = FALSE;

    if (_stricmp(operation, "Create") == 0) {
        if (optionalArg1 == NULL) {
            fprintf(stderr, "Error: Executable path is required for Create.\n");
        }
        else {
            printf("Attempting to create...\n");
            hService = CreateService(scManager, serviceName, serviceName, SERVICE_ALL_ACCESS,
                SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
                optionalArg1, NULL, NULL, NULL, NULL, NULL);
            if (hService != NULL) {
                printf("Service created successfully.\n");
                success = TRUE;
                CloseServiceHandle(hService);
            }
            else {
                printError("CreateService");
            }
        }
    }
    else if (_stricmp(operation, "Delete") == 0) {
        printf("Attempting to delete...\n");
        hService = OpenService(scManager, serviceName, DELETE);
        if (hService != NULL) {
            if (DeleteService(hService)) {
                printf("Service marked for deletion.\n");
                success = TRUE;
            }
            else {
                printError("DeleteService");
            }
            CloseServiceHandle(hService);
        }
        else {
            printError("OpenService (for Delete)");
        }
    }
    else if (_stricmp(operation, "Start") == 0) {
        printf("Attempting to start...\n");
        hService = OpenService(scManager, serviceName, SERVICE_START);
        if (hService != NULL) {
            if (StartService(hService, 0, NULL)) {
                printf("Start command sent.\n");
                success = TRUE;
            }
            else {
                printError("StartService");
            }
            CloseServiceHandle(hService);
        }
        else {
            printError("OpenService (for Start)");
        }
    }
    else if (_stricmp(operation, "Stop") == 0) {
        printf("Attempting to stop...\n");
        hService = OpenService(scManager, serviceName, SERVICE_STOP);
        if (hService != NULL) {
            SERVICE_STATUS status;
            if (ControlService(hService, SERVICE_CONTROL_STOP, &status)) {
                printf("Stop command sent.\n");
                success = TRUE;
            }
            else {
                printError("ControlService (STOP)");
            }
            CloseServiceHandle(hService);
        }
        else {
            printError("OpenService (for Stop)");
        }
    }
    else if (_stricmp(operation, "Pause") == 0) {
        printf("Attempting to pause...\n");
        hService = OpenService(scManager, serviceName, SERVICE_PAUSE_CONTINUE);
        if (hService != NULL) {
            SERVICE_STATUS status;
            if (ControlService(hService, SERVICE_CONTROL_PAUSE, &status)) {
                printf("Pause command sent.\n");
                success = TRUE;
            }
            else {
                printError("ControlService (PAUSE)");
            }
            CloseServiceHandle(hService);
        }
        else {
            printError("OpenService (for Pause)");
        }
    }
    else if (_stricmp(operation, "Continue") == 0) {
        printf("Attempting to continue...\n");
        hService = OpenService(scManager, serviceName, SERVICE_PAUSE_CONTINUE);
        if (hService != NULL) {
            SERVICE_STATUS status;
            if (ControlService(hService, SERVICE_CONTROL_CONTINUE, &status)) {
                printf("Continue command sent.\n");
                success = TRUE;
            }
            else {
                printError("ControlService (CONTINUE)");
            }
            CloseServiceHandle(hService);
        }
        else {
            printError("OpenService (for Continue)");
        }
    }
    else if (_stricmp(operation, "Info") == 0) {
        printf("Getting information...\n");
        hService = OpenService(scManager, serviceName, SERVICE_QUERY_STATUS);
        if (hService != NULL) {
            SERVICE_STATUS_PROCESS ssp;
            DWORD bytesNeeded;
            if (QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(ssp), &bytesNeeded)) {
                printf("  State: %s (PID: %lu, Win32Exit: %lu, SvcExit: %lu)\n",
                    getStateString(ssp.dwCurrentState), ssp.dwProcessId,
                    ssp.dwWin32ExitCode, ssp.dwServiceSpecificExitCode);
                success = TRUE;
            }
            else {
                printError("QueryServiceStatusEx");
            }
            CloseServiceHandle(hService);
        }
        else {
            printError("OpenService (for Info)");
        }
    }
    else if (_stricmp(operation, "Test") == 0) {
        if (optionalArg1 == NULL) {
            fprintf(stderr, "Error: Control code (128-255) is required for Test.\n");
        }
        else {
            int controlCode = atoi(optionalArg1);
            printf("Attempting to send code %d...\n", controlCode);
            if (controlCode >= 128 && controlCode <= 255) {
                hService = OpenService(scManager, serviceName, SERVICE_USER_DEFINED_CONTROL);
                if (hService != NULL) {
                    SERVICE_STATUS status;
                    if (ControlService(hService, (DWORD)controlCode, &status)) {
                        printf("Code %d sent.\n", controlCode);
                        success = TRUE;
                    }
                    else {
                        printError("ControlService (TEST)");
                    }
                    CloseServiceHandle(hService);
                }
                else {
                    printError("OpenService (for Test)");
                }
            }
            else {
                fprintf(stderr, "Error: Invalid code %d. Must be 128-255.\n", controlCode);
            }
        }
    }
    else {
        fprintf(stderr, "Error: Unknown operation '%s'.\n", operation);
    }

    CloseServiceHandle(scManager);
    printf("Operation %s completed %s.\n", operation, success ? "successfully (command sent)" : "with errors");
    return success ? 0 : 1;
}


// Вспомогательные функции
void printError(const char* functionName) {
    DWORD errorCode = GetLastError();
    LPSTR messageBuffer = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    fprintf(stderr, "Error in %s (Code %lu): %s", functionName, errorCode, messageBuffer ? messageBuffer : "Unknown error\n");
    LocalFree(messageBuffer);
}

const char* getStateString(DWORD dwCurrentState) {
    switch (dwCurrentState) {
    case SERVICE_STOPPED: return "STOPPED";
    case SERVICE_START_PENDING: return "START_PENDING";
    case SERVICE_STOP_PENDING: return "STOP_PENDING";
    case SERVICE_RUNNING: return "RUNNING";
    case SERVICE_CONTINUE_PENDING: return "CONTINUE_PENDING";
    case SERVICE_PAUSE_PENDING: return "PAUSE_PENDING";
    case SERVICE_PAUSED: return "PAUSED";
    default: return "UNKNOWN";
    }
}