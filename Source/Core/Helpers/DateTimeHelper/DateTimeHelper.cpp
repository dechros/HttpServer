#include "DateTimeHelper.h"
#include <iostream>
#include <ctime>
#include <stdexcept>

namespace Core::Helpers
{
    const std::string DateTimeHelper::GetCurrentTime()
    {
        time_t now = std::time(nullptr);
        if (now == -1)
        {
            return GetDefaultTime();
        }

        std::tm *tm = std::localtime(&now);
        if (tm == nullptr)
        {
            return GetDefaultTime();
        }

        char buffer[20];
        if (std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm) == 0)
        {
            return GetDefaultTime();
        }

        return std::string(buffer);
    }

    const std::string DateTimeHelper::GetCurrentDateTime(const std::string &separator)
    {
        time_t now = std::time(nullptr);
        if (now == -1)
        {
            return GetDefaultDateTime(separator);
        }

        std::tm *tm = std::localtime(&now);
        if (tm == nullptr)
        {
            return GetDefaultDateTime(separator);
        }

        std::string format;
        if (separator.empty())
        {
            format = "%Y-%m-%d %H:%M:%S";
        }
        else if (separator == "/")
        {
            format = "%Y_%m_%d_%H_%M_%S";
        }
        else
        {
            format = "%Y" + separator + "%m" + separator + "%d" + separator + "%H" + separator + "%M" + separator + "%S";
        }

        char buffer[30];
        if (std::strftime(buffer, sizeof(buffer), format.c_str(), tm) == 0)
        {
            return GetDefaultDateTime(separator);
        }

        return std::string(buffer);
    }

    const std::string DateTimeHelper::GetDefaultTime()
    {
        return "00:00:00";
    }

    const std::string DateTimeHelper::GetDefaultDateTime(const std::string &separator)
    {
        if (separator.empty())
        {
            return "1970-01-01 00:00:00";
        }
        else
        {
            return "1970" + separator + "01" + separator + "01" + separator + "00" + separator + "00" + separator + "00";
        }
    }
}
