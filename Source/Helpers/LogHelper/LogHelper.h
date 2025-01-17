#ifndef LOG_HELPER_H
#define LOG_HELPER_H

#include <string>

namespace Helpers
{
    class LogHelper
    {
    public:
        static std::string FormatLog(const std::string &className, const std::string &methodName, const std::string &message);
    };
}

#endif
