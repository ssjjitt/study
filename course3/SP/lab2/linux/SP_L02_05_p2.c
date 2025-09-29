#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

#define SHM_NAME "/Lab-02"
#define SEM_NAME "/Lab-02e"
#define BUFFER_SIZE (64 * 1024) // 64 KiB
#define ITERATIONS 10

int main() {
    // ��������� ����������� ������
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // ���������� ������
    int* buffer = mmap(NULL, BUFFER_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // ��������� �������
    sem_t* sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    for (int i = 0; i < ITERATIONS; i++) {
        sem_wait(sem); // ��� Writer
        printf("Reader: ����� ������, �������� %d\n", i + 1);
        printf("������: %d %d %d ...\n", buffer[0], buffer[1], buffer[2]);
        sleep(1);
    }

    // ����������� �������
    munmap(buffer, BUFFER_SIZE);
    close(shm_fd);
    sem_close(sem);
    printf("Reader: ���������� ������\n");

    return 0;
}