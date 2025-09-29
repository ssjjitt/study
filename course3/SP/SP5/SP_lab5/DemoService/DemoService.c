#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <errno.h>
#include <shlwapi.h>
#include <shlobj.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Shell32.lib")

#define _CRT_SECURE_NO_WARNINGS

#define DEFAULT_RESERVED_SUBDIR "Reserved"
#define DEFAULT_LOG_SUBDIR "Logs"
#define DEFAULT_INTERVAL 2

char service_name[] = "DemoService"; // Имя сервиса

char base_app_data_dir[MAX_PATH];
char executable_dir[MAX_PATH];
char fixed_log_dir[MAX_PATH] = "C:\\Users\\me0xffff\\AppData\\DemoService\\Logs";

SERVICE_STATUS service_status;
SERVICE_STATUS_HANDLE hServiceStatus;

HANDLE hLogFile = INVALID_HANDLE_VALUE;

// Configuration Variables
char log_path[MAX_PATH];
char source_dir[MAX_PATH];
char reserved_dir[MAX_PATH] = "C:\\Users\\me0xffff\\AppData\\DemoService\\Reserved";
int copy_interval;
BOOL is_paused = FALSE;

// Function Prototypes
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceCtrlHandler(DWORD dwControl);
void WriteLog(const char* formatted_message);
void LogInfo(const char* message);
void LogSuccess(const char* message);
void LogError(const char* message, const char* error_details);
const char* GetStateString(DWORD state);
void ReadConfig();
void CopyFiles();
void CreateOrCheckDir(const char* path, const char* dir_type_name);
BOOL InitializePaths();

int main() {
    SERVICE_TABLE_ENTRY service_table[] = {
        {service_name, ServiceMain},
        {NULL, NULL}
    };

    if (!InitializePaths()) {
        return 1;
    }

    if (!StartServiceCtrlDispatcher(service_table)) {
        if (hLogFile != INVALID_HANDLE_VALUE) CloseHandle(hLogFile);
        return 1;
    }
    return 0;
}

// Service Main Function
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv) {
    BOOL critical_error = FALSE;
    char log_dir_full[MAX_PATH];
    char msg_buffer[MAX_PATH * 3 + 200];

    // 1. Register Control Handler
    hServiceStatus = RegisterServiceCtrlHandler(service_name, ServiceCtrlHandler);
    if (!hServiceStatus) {
        return;
    }

    // 2. Initial Status: START_PENDING
    service_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    service_status.dwCurrentState = SERVICE_START_PENDING;
    service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_PRESHUTDOWN | SERVICE_ACCEPT_PARAMCHANGE;
    service_status.dwWin32ExitCode = NO_ERROR;
    service_status.dwServiceSpecificExitCode = 0;
    service_status.dwCheckPoint = 1;
    service_status.dwWaitHint = 15000;
    SetServiceStatus(hServiceStatus, &service_status);


    // 3. Initialize Base Paths
    if (!InitializePaths()) {
        critical_error = TRUE;
        service_status.dwWin32ExitCode = ERROR_PATH_NOT_FOUND;
    }
    snprintf(msg_buffer, sizeof(msg_buffer), "Base AppData Dir: '%s'", base_app_data_dir);
    WriteLog(msg_buffer);
    service_status.dwCheckPoint++; SetServiceStatus(hServiceStatus, &service_status);

    // 4. Read Configuration
    if (!critical_error) {
        ReadConfig();
        if (strlen(source_dir) == 0) {
            critical_error = TRUE;
            service_status.dwWin32ExitCode = ERROR_BAD_CONFIGURATION;
        }
    }
    service_status.dwCheckPoint++; SetServiceStatus(hServiceStatus, &service_status);

    // 5. Setup Logging Directory (in System AppData)
    if (!critical_error) {
        // Используем статичный путь к логам
        strcpy_s(log_dir_full, MAX_PATH, fixed_log_dir);
        CreateOrCheckDir(log_dir_full, "log");
    }

    // 6. Create Log File Name and Open Handle
    if (!critical_error && strlen(log_dir_full) > 0 && PathFileExists(log_dir_full)) {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        snprintf(log_path, MAX_PATH, "%s\\%04d%02d%02d%02d%02d%02d-service.log",
            log_dir_full, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);

        if (hLogFile == INVALID_HANDLE_VALUE) {
            hLogFile = CreateFile(log_path, FILE_APPEND_DATA, FILE_SHARE_READ, NULL,
                OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        }
        else {
            LogInfo("Log file opened.");
        }
    }
    else {
        log_path[0] = '\0';
    }
    service_status.dwCheckPoint++; SetServiceStatus(hServiceStatus, &service_status);

    // 7. Check/Create Reserved Directory
    if (!critical_error) {
        CreateOrCheckDir(reserved_dir, "reserved backup");
    }
    if (!critical_error) {
        strcpy_s(reserved_dir, MAX_PATH, reserved_dir);
        CreateOrCheckDir(reserved_dir, "reserved backup");
    }
    service_status.dwCheckPoint++; SetServiceStatus(hServiceStatus, &service_status);

    // 8. Validate Source Directory 
    if (!critical_error) {
        DWORD src_attrs = GetFileAttributes(source_dir);
        if (src_attrs == INVALID_FILE_ATTRIBUTES) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Source directory '%s' not found or inaccessible (Error: %lu).", source_dir, GetLastError());
            LogError("Startup Error", msg_buffer);
            critical_error = TRUE;
            service_status.dwWin32ExitCode = ERROR_DIRECTORY;
        }
        else if (!(src_attrs & FILE_ATTRIBUTE_DIRECTORY)) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Source path '%s' is not a directory.", source_dir);
            LogError("Startup Error", msg_buffer);
            critical_error = TRUE;
            service_status.dwWin32ExitCode = ERROR_BAD_PATHNAME;
        }
        else {
            snprintf(msg_buffer, sizeof(msg_buffer), "%s обнаружил каталог %s;", service_name, source_dir);
            LogSuccess(msg_buffer);
        }
    }
    service_status.dwCheckPoint++; SetServiceStatus(hServiceStatus, &service_status);

    // Final Status Update or Stop
    if (critical_error) {
        LogError("Startup Failed", "Critical errors encountered during initialization. Service stopping.");
        service_status.dwCurrentState = SERVICE_STOPPED;
        service_status.dwCheckPoint = 0;
        service_status.dwWaitHint = 0;
        SetServiceStatus(hServiceStatus, &service_status);
        if (hLogFile != INVALID_HANDLE_VALUE) { CloseHandle(hLogFile); hLogFile = INVALID_HANDLE_VALUE; }
        return;
    }

    // 9. Log Successful Start
    char params[MAX_PATH * 2 + 100];
    snprintf(params, sizeof(params), "Source=\"%s\", Reserved=\"%s\", Interval=%d min",
        source_dir, reserved_dir, copy_interval);
    snprintf(msg_buffer, sizeof(msg_buffer), "Сервис %s запущен с параметрами %s;", service_name, params);
    LogSuccess(msg_buffer);

    service_status.dwCurrentState = SERVICE_RUNNING;
    service_status.dwCheckPoint = 0;
    service_status.dwWaitHint = 0;
    SetServiceStatus(hServiceStatus, &service_status);

    // Main Service Loop
    while (service_status.dwCurrentState == SERVICE_RUNNING || service_status.dwCurrentState == SERVICE_PAUSED) {
        if (service_status.dwCurrentState == SERVICE_RUNNING && !is_paused) {
            CopyFiles();
        }
        Sleep(copy_interval * 2 * 1000);
    }

    LogInfo("Service main loop exited. Cleaning up.");
    if (hLogFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hLogFile);
        hLogFile = INVALID_HANDLE_VALUE;
    }
}

// Service Control Request Handler
VOID WINAPI ServiceCtrlHandler(DWORD dwControl) {
    char msg_buffer[MAX_PATH * 3 + 200];
    BOOL trigger_stop = FALSE;
    DWORD previous_state = service_status.dwCurrentState;
    DWORD next_state = previous_state;

    switch (dwControl) {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        next_state = SERVICE_STOPPED;
        service_status.dwWin32ExitCode = NO_ERROR;
        if (hLogFile != INVALID_HANDLE_VALUE) { CloseHandle(hLogFile); hLogFile = INVALID_HANDLE_VALUE; }
        break;

    case SERVICE_CONTROL_PAUSE:
        if (previous_state == SERVICE_RUNNING) {
            is_paused = TRUE;
            next_state = SERVICE_PAUSED;
        }
        else {
            LogInfo("Control: Received PAUSE request, but service not running.");
        }
        break;

    case SERVICE_CONTROL_CONTINUE:
        if (previous_state == SERVICE_PAUSED) {
            is_paused = FALSE;
            next_state = SERVICE_RUNNING;
        }
        else {
            LogInfo("Control: Received CONTINUE request, but service not paused.");
        }
        break;

    case SERVICE_CONTROL_PARAMCHANGE:
        LogInfo("Control: Received PARAMCHANGE signal. Reloading configuration.");
        ReadConfig();
        if (strlen(source_dir) == 0) {
            LogError("Config Error during reload (PARAMCHANGE)", "SourceDir is missing or empty. Stopping service.");
            trigger_stop = TRUE;
            service_status.dwWin32ExitCode = ERROR_BAD_CONFIGURATION;
        }
        else {
            DWORD src_attrs = GetFileAttributes(source_dir);
            if (src_attrs == INVALID_FILE_ATTRIBUTES || !(src_attrs & FILE_ATTRIBUTE_DIRECTORY)) {
                snprintf(msg_buffer, sizeof(msg_buffer), "New Source directory '%s' invalid or inaccessible.", source_dir);
                LogError("Config Error during reload (PARAMCHANGE)", msg_buffer);
                trigger_stop = TRUE;
                service_status.dwWin32ExitCode = ERROR_DIRECTORY;
            }
            else {
                char params[MAX_PATH * 2 + 100];
                snprintf(params, sizeof(params), "Source=\"%s\", Reserved=\"%s\", Interval=%d min", source_dir, reserved_dir, copy_interval);
                snprintf(msg_buffer, sizeof(msg_buffer), "Configuration reloaded successfully via PARAMCHANGE. New params: %s", params);
                LogInfo(msg_buffer);
                CreateOrCheckDir(reserved_dir, "reserved backup");
            }
        }
        break;

    case 131:
        snprintf(msg_buffer, sizeof(msg_buffer), "Привет, это тестовый код из сервиса %s!", service_name);
        LogInfo(msg_buffer);
        SetServiceStatus(hServiceStatus, &service_status);
        return;

    case SERVICE_CONTROL_INTERROGATE:
        LogInfo("Control: Received INTERROGATE request.");
        break;

    default:
        if (dwControl >= 128 && dwControl <= 255) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Control: Received unhandled user control code %lu.", dwControl);
            LogInfo(msg_buffer);
        }
        else {
            snprintf(msg_buffer, sizeof(msg_buffer), "Control: Received unknown control code %lu.", dwControl);
            LogInfo(msg_buffer);
        }
        break;
    }

    if (next_state != previous_state) {
        snprintf(msg_buffer, sizeof(msg_buffer), "Сервис %s сменил состояние с %s на %s",
            service_name, GetStateString(previous_state), GetStateString(next_state));
        LogSuccess(msg_buffer);
        service_status.dwCurrentState = next_state;
    }

    if (trigger_stop) {
        if (service_status.dwCurrentState != SERVICE_STOPPED) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Сервис %s сменил состояние с %s на %s из-за ошибки",
                service_name, GetStateString(previous_state), GetStateString(SERVICE_STOPPED));
            LogSuccess(msg_buffer);
            service_status.dwCurrentState = SERVICE_STOPPED;
        }
        if (hLogFile != INVALID_HANDLE_VALUE) { CloseHandle(hLogFile); hLogFile = INVALID_HANDLE_VALUE; }
    }

    service_status.dwCheckPoint = 0;
    service_status.dwWaitHint = 0;
    SetServiceStatus(hServiceStatus, &service_status);
}

// Logging Functions
void WriteLog(const char* formatted_message) {
    if (log_path[0] == '\0') {
        OutputDebugStringA("WriteLog skipped: log_path is empty\n");
        return;
    }

    if (hLogFile == INVALID_HANDLE_VALUE) {
        hLogFile = CreateFile(log_path, FILE_APPEND_DATA, FILE_SHARE_READ, NULL,
            OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hLogFile == INVALID_HANDLE_VALUE) {
            char errMsg[256];
            snprintf(errMsg, sizeof(errMsg), "WriteLog: Failed to open log file '%s', error %lu\n", log_path, GetLastError());
            OutputDebugStringA(errMsg);
            return;
        }
        else {
            OutputDebugStringA("WriteLog: Log file opened successfully.\n");
        }
    }

    if (hLogFile != INVALID_HANDLE_VALUE) {
        char timestamp[32];
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        snprintf(timestamp, sizeof(timestamp), "%02d:%02d:%02d ", t->tm_hour, t->tm_min, t->tm_sec);

        char full_msg[2048];
        snprintf(full_msg, sizeof(full_msg), "%s%s\r\n", timestamp, formatted_message);
        OutputDebugStringA(full_msg);
        DWORD bytes_written;
        WriteFile(hLogFile, full_msg, (DWORD)strlen(full_msg), &bytes_written, NULL);
        FlushFileBuffers(hLogFile);
    }
}

void LogInfo(const char* message) {
    WriteLog(message);
}

void LogSuccess(const char* message) {
    char success_msg[1536];
    snprintf(success_msg, sizeof(success_msg), "Успех! %s", message);
    WriteLog(success_msg);
}

void LogError(const char* operation_summary, const char* error_details) {
    char error_msg[1536];
    snprintf(error_msg, sizeof(error_msg), "Попытка выполнения операции сервисом провалена! %s: %s!",
        operation_summary, error_details);
    WriteLog(error_msg);
}


// Configuration Reading Function
void ReadConfig() {
    char config_path[MAX_PATH];
    char temp_source[MAX_PATH] = "";
    char temp_reserved[MAX_PATH] = "";
    char default_reserved_full[MAX_PATH];
    char msg_buffer[MAX_PATH + 200];

    if (strlen(executable_dir) == 0) {
        LogError("ReadConfig", "Executable directory path not initialized. Cannot locate config.ini.");
        copy_interval = DEFAULT_INTERVAL;
        strcpy_s(source_dir, MAX_PATH, "");
        if (strlen(base_app_data_dir) > 0) PathCombine(reserved_dir, base_app_data_dir, DEFAULT_RESERVED_SUBDIR);
        else strcpy_s(reserved_dir, MAX_PATH, "");
        return;
    }
    PathCombine(config_path, executable_dir, "config.ini");

    snprintf(msg_buffer, sizeof(msg_buffer), "Attempting to read configuration from '%s'", config_path);
    LogInfo(msg_buffer);

    copy_interval = DEFAULT_INTERVAL;
    strcpy_s(source_dir, MAX_PATH, "");
    if (strlen(base_app_data_dir) > 0) {
        PathCombine(default_reserved_full, base_app_data_dir, DEFAULT_RESERVED_SUBDIR);
        strcpy_s(reserved_dir, MAX_PATH, default_reserved_full);
    }
    else {
        LogInfo("Config Warning: Cannot determine default Reserved directory path (%APPDATA% inaccessible).");
        default_reserved_full[0] = '\0';
        strcpy_s(reserved_dir, MAX_PATH, "");
    }

    if (!PathFileExists(config_path)) {
        snprintf(msg_buffer, sizeof(msg_buffer), "Config Warning: File not found at '%s'. Using default settings.", config_path);
        LogInfo(msg_buffer);
    }
    else {
        LogInfo("Config: Found config.ini. Reading settings...");
        GetPrivateProfileString("Settings", "SourceDir", "", temp_source, MAX_PATH, config_path);
        if (strlen(temp_source) == 0) {
            LogError("ReadConfig", "'SourceDir' setting is missing or empty in config.ini. This is required.");
        }
        else {
            strcpy_s(source_dir, MAX_PATH, temp_source);
            snprintf(msg_buffer, sizeof(msg_buffer), "Config: Read SourceDir = %s", source_dir);
            LogInfo(msg_buffer);
        }

        GetPrivateProfileString("Settings", "ReservedDir",
            (default_reserved_full[0] != '\0' ? default_reserved_full : ""),
            temp_reserved, MAX_PATH, config_path);

        if (strlen(temp_reserved) == 0 && default_reserved_full[0] == '\0') {
            LogError("ReadConfig", "'ReservedDir' not found in config and default AppData path failed. Backup disabled.");
            strcpy_s(reserved_dir, MAX_PATH, "");
        }
        else if (strlen(temp_reserved) == 0 && default_reserved_full[0] != '\0') {
            snprintf(msg_buffer, sizeof(msg_buffer), "Config: 'ReservedDir' not found. Using default: %s", reserved_dir);
            LogInfo(msg_buffer);
        }
        else {
            if (PathIsRelative(temp_reserved)) {
                PathCombine(reserved_dir, executable_dir, temp_reserved);
                snprintf(msg_buffer, sizeof(msg_buffer), "Config: Read relative ReservedDir = %s. Resolved to: %s", temp_reserved, reserved_dir);
                LogInfo(msg_buffer);
            }
            else {
                strcpy_s(reserved_dir, MAX_PATH, temp_reserved);
                snprintf(msg_buffer, sizeof(msg_buffer), "Config: Read absolute ReservedDir = %s", reserved_dir);
                LogInfo(msg_buffer);
            }
        }

        copy_interval = GetPrivateProfileInt("Settings", "Interval", DEFAULT_INTERVAL, config_path);
        snprintf(msg_buffer, sizeof(msg_buffer), "Config: Read Interval = %d minutes.", copy_interval);
        LogInfo(msg_buffer);

        if (copy_interval <= 0) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Config Warning: Invalid Interval value (%d). Using default %d minutes.", copy_interval, DEFAULT_INTERVAL);
            LogInfo(msg_buffer);
            copy_interval = DEFAULT_INTERVAL;
        }
    }

    snprintf(msg_buffer, sizeof(msg_buffer), "Config Loaded: Source='%s', Reserved='%s', Interval=%d min.",
        source_dir[0] != '\0' ? source_dir : "[Not Set/Invalid]",
        reserved_dir[0] != '\0' ? reserved_dir : "[Not Set/Invalid]",
        copy_interval);
    LogInfo(msg_buffer);
}

// File Copying Function
void CopyFiles() {
    char search_path[MAX_PATH];
    char src_file[MAX_PATH], dst_file[MAX_PATH];
    char msg_buffer[MAX_PATH * 2 + 100];
    WIN32_FIND_DATA fd;
    HANDLE hFind;
    BOOL copied_any = FALSE;

    if (source_dir[0] == '\0' || reserved_dir[0] == '\0') {
        LogError("Backup Skipped", "Source or Reserved directory not configured correctly.");
        return;
    }
    CreateOrCheckDir(reserved_dir, "reserved backup");

    snprintf(search_path, sizeof(search_path), "%s\\*.*", source_dir);
    hFind = FindFirstFile(search_path, &fd);

    if (hFind == INVALID_HANDLE_VALUE) {
        if (GetLastError() != ERROR_FILE_NOT_FOUND) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Cannot access source directory '%s' for listing. Error: %lu", source_dir, GetLastError());
            LogError("Backup Error", msg_buffer);
        }
        else {
            LogInfo("Backup Info: Source directory is empty or contains no matching files.");
        }
        return;
    }

    LogInfo("Backup: Starting file copy cycle...");
    do {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;

        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            PathCombine(src_file, source_dir, fd.cFileName);
            PathCombine(dst_file, reserved_dir, fd.cFileName);

            if (CopyFile(src_file, dst_file, FALSE)) {
                snprintf(msg_buffer, sizeof(msg_buffer), "Сервис %s успешно создал резервную копию файла %s", service_name, fd.cFileName);
                LogSuccess(msg_buffer);
                copied_any = TRUE;
            }
            else {
                snprintf(msg_buffer, sizeof(msg_buffer), "Failed to copy file '%s' to '%s'. Error: %lu", src_file, dst_file, GetLastError());
                LogError("Backup Error", msg_buffer);
            }
        }
    } while (FindNextFile(hFind, &fd));

    FindClose(hFind);

    if (copied_any) {
        LogInfo("Backup: File copy cycle completed.");
    }
    else {
        LogInfo("Backup: No files were copied in this cycle.");
    }
}

// Directory Creation/Check Function
void CreateOrCheckDir(const char* path, const char* dir_type_name) {
    char msg_buffer[MAX_PATH + 200];
    DWORD attrs;

    if (path == NULL || path[0] == '\0') {
        snprintf(msg_buffer, sizeof(msg_buffer), "Cannot check/create null or empty path for '%s' directory.", dir_type_name);
        LogError("Directory Error", msg_buffer);
        return;
    }

    attrs = GetFileAttributes(path);

    if (attrs == INVALID_FILE_ATTRIBUTES) {
        if (_mkdir(path) == 0) {
            snprintf(msg_buffer, sizeof(msg_buffer), "%s создал каталог %s;", service_name, path);
            LogSuccess(msg_buffer);
        }
        else {
            snprintf(msg_buffer, sizeof(msg_buffer), "Failed to create %s directory '%s' (errno: %d)", dir_type_name, path, errno);
            LogError("Directory Creation", msg_buffer);
        }
    }
    else if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
        snprintf(msg_buffer, sizeof(msg_buffer), "%s обнаружил каталог %s;", service_name, path);
        LogSuccess(msg_buffer);
    }
    else {
        snprintf(msg_buffer, sizeof(msg_buffer), "Path '%s' for %s directory exists but is not a directory.", path, dir_type_name);
        LogError("Directory Error", msg_buffer);
    }
}

// Helper Function to Initialize Base Paths
BOOL InitializePaths() {
    if (GetModuleFileName(NULL, executable_dir, MAX_PATH) == 0) return FALSE;
    PathRemoveFileSpec(executable_dir);

    if (FAILED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, base_app_data_dir))) {
        base_app_data_dir[0] = '\0';
    }
    else {
        PathCombine(base_app_data_dir, base_app_data_dir, "DemoService");
    }
    return TRUE;
}

const char* GetStateString(DWORD state) {
    switch (state) {
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