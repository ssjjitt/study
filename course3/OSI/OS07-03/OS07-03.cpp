#include <iostream>
#include <Windows.h>

int main() {
    setlocale(LC_ALL, "rus");

    // Создаем ожидающий таймер
    HANDLE hTimer = CreateWaitableTimer(nullptr, TRUE, L"MyTimer");
    if (hTimer == nullptr) {
        std::cerr << "Не удалось создать таймер." << std::endl;
        return 1;
    }

    const LONG period = 1000; // Период 1 секунда
    const LONG outputInterval = 3000; // Интервал вывода 3 секунды
    const LONG totalDuration = 15000; // Общая продолжительность 15 секунд

    LARGE_INTEGER dueTime;
    dueTime.QuadPart = -period * 10000; // Устанавливаем время срабатывания таймера
    SetWaitableTimer(hTimer, &dueTime, period, nullptr, nullptr, FALSE);

    int iterations = 0;
    DWORD lastOutputTime = GetTickCount();
    DWORD startTime = GetTickCount();

    while ((GetTickCount() - startTime) < totalDuration) {
        // Ожидаем срабатывания таймера
        if (WaitForSingleObject(hTimer, INFINITE) == WAIT_OBJECT_0) {
            iterations++; // Увеличиваем счетчик итераций
        }

        // Получаем текущее время
        DWORD currentTime = GetTickCount();

        // Проверяем, пришло ли время для вывода
        if (currentTime - lastOutputTime >= outputInterval) {
            std::cout << "Количество итераций: " << iterations << std::endl;
            lastOutputTime = currentTime; // Обновляем время последнего вывода
        }
    }

    std::cout << "Общее количество итераций: " << iterations << std::endl;

    // Останавливаем таймер и закрываем его
    CancelWaitableTimer(hTimer);
    CloseHandle(hTimer);

    return 0;
}