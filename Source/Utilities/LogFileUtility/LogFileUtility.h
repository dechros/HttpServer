#ifndef LOG_FILE_UTILITY_H
#define LOG_FILE_UTILITY_H

#include <string>
#include <mutex>

namespace Utilities
{
    class LogFileUtility
    {
    private:
        constexpr static int MAX_LOG_SIZE_MB = 100;
        constexpr static std::string FILE_EXTENSION = ".txt";
        constexpr static std::string LOGS_PATH = "./Logs";
        static const std::string FILE_BASE_NAME;
        static int logFileSuffix;
        static std::mutex logFileMutex;

        static std::string GetLogFileName();

    public:
        static bool Log(const std::string &className, const std::string &methodName, const std::string &message);
        static bool Log(const std::string &message);
    };
}
#endif