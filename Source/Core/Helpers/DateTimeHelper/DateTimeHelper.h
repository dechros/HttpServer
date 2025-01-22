#ifndef DATE_TIME_HELPER_H
#define DATE_TIME_HELPER_H

#include <string>

namespace Core::Helpers
{
    class DateTimeHelper
    {
    private:
        static const std::string GetDefaultTime();
        static const std::string GetDefaultDateTime(const std::string &separator);

    public:
        static const std::string GetCurrentTime();
        static const std::string GetCurrentDateTime(const std::string &separator = "");
    };
}

#endif
