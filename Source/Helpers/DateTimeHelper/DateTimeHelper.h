#ifndef DATE_TIME_HELPER_H
#define DATE_TIME_HELPER_H

#include <string>

namespace Helpers
{
    class DateTimeHelper
    {
    public:
        static std::string GetCurrentDateTime();
        static std::string GetCurrentDateTimeUnderline();
    };
}

#endif