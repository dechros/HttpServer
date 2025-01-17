#include "ConsoleUtility.h"
#include "LogHelper.h"
#include <iostream>

namespace Utilities
{
    std::mutex ConsoleUtility::consoleMutex;

    void ConsoleUtility::Log(const std::string &className, const std::string &methodName, const std::string &message)
    {
        std::unique_lock<std::mutex> lock(consoleMutex);
        std::cout << Helpers::LogHelper::FormatLog(className, methodName, message) << std::endl;
    }

    void ConsoleUtility::Log(const std::string &message)
    {
        std::unique_lock<std::mutex> lock(consoleMutex);
        std::cout << message << std::endl;
    }

    void ConsoleUtility::Clear()
    {
        std::unique_lock<std::mutex> lock(consoleMutex);
        std::cout << "\033[2J\033[1;1H";
    }
}