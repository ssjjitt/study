#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH "lab02d.txt"
#define FILE_SIZE (64 * 1024)
#define OFFSET 0
#define NEW_DATA "ubi defuit orbis"

void handleError(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void show_proc_maps() {
    int pid = getppid();
    printf("\n=== /proc/self/maps ===\n");
    printf("PID:%d\n", pid);
    system("cat /proc/self/maps");
}

int main(int argc, char* argv[]) {
    char* mapped;
    int fd;
    struct stat sb;

    fd = open(FILE_PATH, O_RDWR | O_CREAT, 0666);

    if (fd == -1)
        handleError("Error: cant open file");

    if (ftruncate(fd, FILE_SIZE) == -1)
        handleError("Error: cant increase size of file");

    if (fstat(fd, &sb) == -1)
        handleError("Error: no stats");
    mapped = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, OFFSET);
    if (mapped == MAP_FAILED)
        handleError("Error: mmap is failed");

    printf("File mapped into memory /proc/self/maps\n");
    show_proc_maps();
    getchar();

    printf("Текущее содержимое файла:\n%s\n", mapped);
    getchar();
    memcpy(mapped, NEW_DATA, strlen(NEW_DATA));
    printf("Записаны новые данные:%s\n", NEW_DATA);
    getchar();
    if (msync(mapped, FILE_SIZE, MS_SYNC) == -1) handleError("Error msync");
    printf("Данные выгружены на диск(msync).\n");
    getchar();

    printf("Текущее содержимое файла:\n%s\n", mapped);
    getchar();
    printf("In memory:\n");
    show_proc_maps();
    getchar();
    if (munmap(mapped, FILE_SIZE) == -1) handleError("Error munmap");
    close(fd);

    return 0;
}
