#ifndef LOG_CONSOLE_UTILITY_H
#define LOG_CONSOLE_UTILITY_H

#include <string>
#include <mutex>
#include "LogEntry.h"

namespace Core::Utilities
{
    class LogConsoleUtility
    {
    private:
        static std::mutex consoleMutex;

    public:
        static void Clear();
        static void Log(const Core::Types::LogEntry &logEntry);
    };
}

#endif
