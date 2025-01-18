#include "LogConsoleUtility.h"
#include <iostream>

namespace Core::Utilities
{
    std::mutex LogConsoleUtility::consoleMutex;

    void LogConsoleUtility::Log(const Core::Types::LogEntry &logEntry)
    {
        std::unique_lock<std::mutex> lock(consoleMutex);
        std::cout << logEntry.GetFormattedLog() << std::endl;
    }

    void LogConsoleUtility::Clear()
    {
        std::unique_lock<std::mutex> lock(consoleMutex);
        std::cout << "\033[2J\033[1;1H";
    }
}