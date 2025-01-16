#include "DateTimeHelper.h"
#include <iostream>
#include <ctime>

namespace Helpers
{
    std::string DateTimeHelper::GetCurrentDateTime()
    {
        time_t now = std::time(nullptr);
        std::tm *tm = std::localtime(&now);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", tm);
        std::string currentDateTime = buffer;
        return currentDateTime;
    }
}
