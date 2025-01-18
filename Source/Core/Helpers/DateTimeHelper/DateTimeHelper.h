#ifndef DATE_TIME_HELPER_H
#define DATE_TIME_HELPER_H

#include <string>

namespace Core::Helpers
{
    class DateTimeHelper
    {
    public:
        static std::string GetCurrentTime();
        static std::string GetCurrentDateTime(const std::string &separator = "");
    };
}

#endif
