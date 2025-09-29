#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <ini.h>

// Константы и Значения по умолчанию
#define CONFIG_FILE "/etc/demoserviced/demoserviced.conf"

#define DEFAULT_LOG_DIR "/var/log/demoserviced"
#define DEFAULT_RESERVED_DIR "/srv/demoserviced/reserved"
#define DEFAULT_SOURCE_DIR ""
#define DEFAULT_INTERVAL 60
#define MAX_PATH 4096 

// Глобальные переменные
static volatile sig_atomic_t g_running = 1;
static volatile sig_atomic_t g_reload_config_flag = 0;
static char g_service_name[] = "demoserviced";
static FILE* g_log_fp = NULL;

// Пути и интервал (читаются из конфига)
static char g_log_dir_path[MAX_PATH];
static char g_current_log_file_path[MAX_PATH];
static char g_source_dir[MAX_PATH];
static char g_reserved_dir[MAX_PATH];
static int g_copy_interval;

// Прототипы функций
void SignalHandler(int sig);
void Daemonize();
int IniHandler(void* user, const char* section, const char* name, const char* value);
void ReadConfig();
void CreateOrCheckDir(const char* path, const char* dir_type_name);
void InitializeLogging();
void CloseLogFile();
void WriteLog(const char* formatted_message);
void LogInfo(const char* message);
void LogSuccess(const char* message);
void LogError(const char* operation_summary, const char* error_details);
void CopyFiles();

// Точка входа
int main() {
    // 1. Демонизация
    Daemonize();

    // 2. Установка обработчиков сигналов
    struct sigaction sa;
    sa.sa_handler = SignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGTERM, &sa, NULL) < 0 || sigaction(SIGHUP, &sa, NULL) < 0 || sigaction(SIGINT, &sa, NULL) < 0) {
        exit(EXIT_FAILURE);
    }

    // 3. Инициализация
    ReadConfig();
    InitializeLogging();

    // 4. Проверка SourceDir
    struct stat st;
    if (g_source_dir[0] == '\0') {
        LogError("Startup Error", "SourceDir parameter is missing or empty in configuration file. Service stopping.");
        CloseLogFile();
        exit(EXIT_FAILURE);
    }
    if (stat(g_source_dir, &st) != 0) {
        char err_details[MAX_PATH + 50];
        snprintf(err_details, sizeof(err_details), "Source directory '%s' not found (%s). Service stopping.", g_source_dir, strerror(errno));
        LogError("Startup Error", err_details);
        CloseLogFile();
        exit(EXIT_FAILURE);
    }
    else if (!S_ISDIR(st.st_mode)) {
        char err_details[MAX_PATH + 50];
        snprintf(err_details, sizeof(err_details), "Source path '%s' is not a directory. Service stopping.", g_source_dir);
        LogError("Startup Error", err_details);
        CloseLogFile();
        exit(EXIT_FAILURE);
    }
    else {
        char msg_buffer[MAX_PATH + 100];
        snprintf(msg_buffer, sizeof(msg_buffer), "%s обнаружил каталог %s;", g_service_name, g_source_dir);
        LogSuccess(msg_buffer);
    }

    // 5. Создание/Проверка ReservedDir
    CreateOrCheckDir(g_reserved_dir, "reserved backup");

    // 6. Логирование успешного запуска
    char params[MAX_PATH * 2 + 100];
    snprintf(params, sizeof(params), "Source=\"%s\", Reserved=\"%s\", Interval=%d min",
        g_source_dir, g_reserved_dir, g_copy_interval);
    char msg_buffer[sizeof(params) + 100];
    snprintf(msg_buffer, sizeof(msg_buffer), "Сервис %s запущен с параметрами %s;", g_service_name, params);
    LogSuccess(msg_buffer);

    // Основной цикл
    while (g_running) {
        if (g_reload_config_flag) {
            LogInfo("SIGHUP received. Reloading configuration...");
            CloseLogFile();
            ReadConfig();
            InitializeLogging();

            if (g_source_dir[0] == '\0') {
                LogError("Config Reload Error", "SourceDir is missing after reload. Stopping.");
                g_running = 0;
            }
            else if (stat(g_source_dir, &st) != 0 || !S_ISDIR(st.st_mode)) {
                char err_details[MAX_PATH + 50];
                snprintf(err_details, sizeof(err_details), "Source directory '%s' invalid after reload. Stopping.", g_source_dir);
                LogError("Config Reload Error", err_details);
                g_running = 0;
            }
            else {
                CreateOrCheckDir(g_reserved_dir, "reserved backup");
                LogInfo("Configuration reloaded successfully.");
            }
            g_reload_config_flag = 0;
        }

        if (g_running) {
            CopyFiles();
            unsigned int sleep_seconds = g_copy_interval * 60;
            while (sleep_seconds > 0 && g_running && !g_reload_config_flag) {
                sleep_seconds = sleep(sleep_seconds);
            }
        }
    }

    // Завершение работы
    snprintf(msg_buffer, sizeof(msg_buffer), "Сервис %s завершает работу по сигналу;", g_service_name);
    LogSuccess(msg_buffer);
    CloseLogFile();
    exit(EXIT_SUCCESS);
}

// Функция Демонизации
void Daemonize() {
    pid_t pid;

    // 1. Первый fork
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    // 2. Смена маски файлов
    umask(0);

    // 3. Создание новой сессии
    if (setsid() < 0) exit(EXIT_FAILURE);

    // 4. Второй fork для предотвращения получения терминала
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    // 5. Смена рабочего каталога на корень
    if (chdir("/") < 0) exit(EXIT_FAILURE);

    // 6. Закрытие стандартных файловых дескрипторов
    close(STDIN_FILENO);

    int fd_null = open("/dev/null", O_RDWR);
    if (fd_null != -1) {
        dup2(fd_null, STDOUT_FILENO);
        dup2(fd_null, STDERR_FILENO);
        if (fd_null > 2) close(fd_null);
    }
    else {
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }
}

// Обработчик Сигналов 
void SignalHandler(int sig) {
    if (sig == SIGTERM || sig == SIGINT) {
        g_running = 0;
    }
    else if (sig == SIGHUP) {
        g_reload_config_flag = 1;
    }
}

// Функции Логирования
void WriteLog(const char* formatted_message) {
    if (g_current_log_file_path[0] == '\0') return;

    if (!g_log_fp) {
        g_log_fp = fopen(g_current_log_file_path, "a");
        if (!g_log_fp) return;
    }

    char timestamp[32];
    time_t now = time(NULL);
    struct tm t;
    localtime_r(&now, &t);
    snprintf(timestamp, sizeof(timestamp), "%02d:%02d:%02d ", t.tm_hour, t.tm_min, t.tm_sec);

    fprintf(g_log_fp, "%s%s\n", timestamp, formatted_message);
    fflush(g_log_fp);
}

void LogInfo(const char* message) { WriteLog(message); }

void LogSuccess(const char* message) {
    char success_msg[MAX_PATH * 2];
    snprintf(success_msg, sizeof(success_msg), "Успех! %s", message);
    WriteLog(success_msg);
}

void LogError(const char* operation_summary, const char* error_details) {
    char error_msg[MAX_PATH * 2];
    // Формат #6
    snprintf(error_msg, sizeof(error_msg), "Попытка выполнения операции сервисом провалена! %s: %s!",
        operation_summary, error_details);
    WriteLog(error_msg);
}

void CloseLogFile() {
    if (g_log_fp) {
        fclose(g_log_fp);
        g_log_fp = NULL;
    }
}

void InitializeLogging() {
    CreateOrCheckDir(g_log_dir_path, "log");

    struct stat st;
    if (stat(g_log_dir_path, &st) == 0 && S_ISDIR(st.st_mode)) {
        time_t now = time(NULL);
        struct tm t;
        localtime_r(&now, &t);
        snprintf(g_current_log_file_path, sizeof(g_current_log_file_path), "%s/%04d%02d%02d%02d%02d%02d-service.log",
            g_log_dir_path, t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
            t.tm_hour, t.tm_min, t.tm_sec);

        LogInfo("Logging initialized.");
    }
    else {
        g_current_log_file_path[0] = '\0';
    }
}

// Обработчик для ini_parse
int IniHandler(void* user, const char* section, const char* name, const char* value) {
#define MATCH(s, n) strcasecmp(section, s) == 0 && strcasecmp(name, n) == 0

    if (MATCH("Settings", "SourceDir")) {
        strncpy(g_source_dir, value, sizeof(g_source_dir) - 1);
        g_source_dir[sizeof(g_source_dir) - 1] = '\0';
    }
    else if (MATCH("Settings", "ReservedDir")) {
        strncpy(g_reserved_dir, value, sizeof(g_reserved_dir) - 1);
        g_reserved_dir[sizeof(g_reserved_dir) - 1] = '\0';
    }
    else if (MATCH("Settings", "LogDir")) { // Читаем путь к логам
        strncpy(g_log_dir_path, value, sizeof(g_log_dir_path) - 1);
        g_log_dir_path[sizeof(g_log_dir_path) - 1] = '\0';
    }
    else if (MATCH("Settings", "Interval")) {
        g_copy_interval = atoi(value);
        if (g_copy_interval <= 0) g_copy_interval = DEFAULT_INTERVAL;
    }
    else {
        return 0;
    }
    return 1;
#undef MATCH
}

// Чтение Конфигурации
void ReadConfig() {
    strncpy(g_log_dir_path, DEFAULT_LOG_DIR, sizeof(g_log_dir_path) - 1);
    g_log_dir_path[sizeof(g_log_dir_path) - 1] = '\0';
    strncpy(g_source_dir, DEFAULT_SOURCE_DIR, sizeof(g_source_dir) - 1);
    g_source_dir[sizeof(g_source_dir) - 1] = '\0';
    strncpy(g_reserved_dir, DEFAULT_RESERVED_DIR, sizeof(g_reserved_dir) - 1);
    g_reserved_dir[sizeof(g_reserved_dir) - 1] = '\0';
    g_copy_interval = DEFAULT_INTERVAL;

    if (ini_parse(CONFIG_FILE, IniHandler, NULL) < 0) {
        LogInfo("Warning: Cannot load config file. Using default settings.");
    }
}

// Копирование Файлов
void CopyFiles() {
    DIR* dir = opendir(g_source_dir);
    char msg_buffer[MAX_PATH * 2 + 100];
    struct stat st_source_dir;

    if (!dir || stat(g_source_dir, &st_source_dir) != 0 || !S_ISDIR(st_source_dir.st_mode)) {
        snprintf(msg_buffer, sizeof(msg_buffer), "Cannot access source directory '%s' (%s)",
            g_source_dir, dir ? "Not a directory?" : strerror(errno));
        LogError("CopyFiles Error", msg_buffer);
        if (dir) closedir(dir);
        return;
    }

    struct dirent* entry;
    bool copied_any = false;
    LogInfo("Backup: Starting file copy cycle...");

    while ((entry = readdir(dir)) != NULL) {
        char src_file[MAX_PATH];
        char dst_file[MAX_PATH];
        struct stat st_file;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        snprintf(src_file, sizeof(src_file), "%s/%s", g_source_dir, entry->d_name);

        if (lstat(src_file, &st_file) != 0 || !S_ISREG(st_file.st_mode)) continue;

        snprintf(dst_file, sizeof(dst_file), "%s/%s", g_reserved_dir, entry->d_name);

        int src_fd = open(src_file, O_RDONLY);
        if (src_fd < 0) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Failed to open source file '%s' (%s)", entry->d_name, strerror(errno));
            LogError("CopyFiles Error", msg_buffer);
            continue;
        }

        int dst_fd = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dst_fd < 0) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Failed to open/create destination file '%s' (%s)", entry->d_name, strerror(errno));
            LogError("CopyFiles Error", msg_buffer);
            close(src_fd);
            continue;
        }

        char buffer[8192];
        ssize_t bytes_read, bytes_written;
        int error_occurred = 0;

        while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
            char* ptr = buffer;
            while (bytes_read > 0) {
                bytes_written = write(dst_fd, ptr, bytes_read);
                if (bytes_written <= 0) {
                    snprintf(msg_buffer, sizeof(msg_buffer), "Failed to write to file '%s' (%s)", entry->d_name, strerror(errno));
                    LogError("CopyFiles Error", msg_buffer);
                    error_occurred = 1;
                    break;
                }
                bytes_read -= bytes_written;
                ptr += bytes_written;
            }
            if (error_occurred) break;
        }

        if (bytes_read < 0) { // Ошибка чтения
            snprintf(msg_buffer, sizeof(msg_buffer), "Failed to read from file '%s' (%s)", entry->d_name, strerror(errno));
            LogError("CopyFiles Error", msg_buffer);
            error_occurred = 1;
        }

        close(src_fd);
        close(dst_fd);

        if (!error_occurred) {
            snprintf(msg_buffer, sizeof(msg_buffer), "Сервис %s успешно создал резервную копию файла %s;", g_service_name, entry->d_name);
            LogSuccess(msg_buffer);
            copied_any = true;
        }
    }
    closedir(dir);

    if (copied_any) {
        LogInfo("Backup: File copy cycle completed.");
    }
    else {
        LogInfo("Backup: No regular files found or copied in this cycle.");
    }
}

// Создание/Проверка Каталога
void CreateOrCheckDir(const char* path, const char* dir_type_name) {
    char msg_buffer[MAX_PATH + 200];
    struct stat st;

    if (path == NULL || path[0] == '\0') {
        snprintf(msg_buffer, sizeof(msg_buffer), "Path is null or empty for '%s' directory.", dir_type_name);
        LogError("Directory Error", msg_buffer);
        return;
    }

    if (stat(path, &st) != 0) {
        if (errno == ENOENT) {
            if (mkdir(path, 0755) == 0) { // Права rwxr-xr-x
                snprintf(msg_buffer, sizeof(msg_buffer), "%s создал каталог %s;", g_service_name, path);
                LogSuccess(msg_buffer);
            }
            else {
                snprintf(msg_buffer, sizeof(msg_buffer), "Failed to create %s directory '%s' (%s)", dir_type_name, path, strerror(errno));
                LogError("Directory Creation", msg_buffer);
            }
        }
        else {
            snprintf(msg_buffer, sizeof(msg_buffer), "Failed to check path for %s directory '%s' (%s)", dir_type_name, path, strerror(errno));
            LogError("Directory Check Error", msg_buffer);
        }
    }
    else if (S_ISDIR(st.st_mode)) {
        snprintf(msg_buffer, sizeof(msg_buffer), "%s обнаружил каталог %s;", g_service_name, path);
        LogSuccess(msg_buffer);
    }
    else {
        snprintf(msg_buffer, sizeof(msg_buffer), "Path '%s' for %s directory exists but is not a directory.", path, dir_type_name);
        LogError("Directory Error", msg_buffer);
    }
}