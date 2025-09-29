#include <iostream>
#include <iomanip>
#include <ctime>

int main() {
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;

    localtime_s(&localTime, &currentTime);

    std::cout << std::put_time(&localTime, "%d.%m.%Y %H:%M:%S") << std::endl;

    return 0;
}