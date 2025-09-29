#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/Lab-02"
#define SEM_NAME "/Lab-02e"
#define BUFFER_SIZE (64 * 1024) // 64 KiB
#define ITERATIONS 10

int main() {
    // ��������� ��� ������� ����������� ������
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }
    ftruncate(shm_fd, BUFFER_SIZE);

    // ���������� � ������
    int* buffer = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // ������� �������
    sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    for (int i = 0; i < ITERATIONS; i++) {
        printf("Writer: ��������� ������, �������� %d\n", i + 1);
        for (int j = 0; j < (BUFFER_SIZE / sizeof(int)); j++) {
            buffer[j] = i * 1000 + j;
        }
        sem_post(sem);  // ������������ reader
        sleep(1);
    }

    // ����������� �������
    munmap(buffer, BUFFER_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);
    printf("Writer: ���������� ������\n");

    return 0;
}