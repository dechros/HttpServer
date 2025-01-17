#ifndef CONSOLE_HELPER_H
#define CONSOLE_HELPER_H

#include <string>
#include <mutex>

namespace Utilities
{
    class ConsoleUtility
    {
    private:
        static std::mutex consoleMutex;

    public:
        static void Clear();
        static void Log(const std::string &message, const std::string &className, const std::string &methodName);
        static void Log(const std::string &message);
    };
}

#endif
