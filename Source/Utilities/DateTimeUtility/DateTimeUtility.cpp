#include "DateTimeUtility.h"
#include <iostream>
#include <ctime>

namespace Utilities
{
    std::string DateTimeUtility::GetCurrentTime()
    {
        std::string defaultTime = "00:00:00";

        time_t now = std::time(nullptr);
        if (now == -1)
        {
            return defaultTime;
        }

        std::tm *tm = std::localtime(&now);
        if (tm == nullptr)
        {
            return defaultTime;
        }

        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);

        return std::string(buffer);
    }

    std::string DateTimeUtility::GetCurrentDateTime(const std::string &separator)
    {
        std::string defaultDateTime;
        if (separator.empty())
        {
            defaultDateTime = "1970-01-01 00:00:00";
        }
        else
        {
            defaultDateTime = "1970" + separator + "01" + separator + "01" + separator + "00" + separator + "00" + separator + "00";
        }

        time_t now = std::time(nullptr);
        if (now == -1)
        {
            return defaultDateTime;
        }

        std::tm *tm = std::localtime(&now);
        if (tm == nullptr)
        {
            return defaultDateTime;
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
        std::strftime(buffer, sizeof(buffer), format.c_str(), tm);

        return std::string(buffer);
    }
}
