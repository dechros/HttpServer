#ifndef LOG_HELPER_H
#define LOG_HELPER_H

#include <string>
#include <fstream>
#include <filesystem>

namespace Helpers
{
    class LogHelper
    {
    private:
        constexpr static std::string FILE_EXTENSION = ".txt";
        std::ofstream logFile;
        std::string logDirectory;
        std::string baseFileName;
        int maxFileSize;
        int fileSuffix = 0;

        std::string GetLogFilePath();

    public:
        LogHelper(const std::string &directory, const std::string &baseName, const int maxSize);
        void LogToFile(const std::string &message);
        ~LogHelper();
    };
}

#endif
