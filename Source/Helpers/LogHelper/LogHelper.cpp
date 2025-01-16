#include "LogHelper.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>

namespace Helpers
{
    LogHelper::LogHelper(const std::string &directory, const std::string &baseName, const int maxSize) : logDirectory(directory), baseFileName(baseName), maxFileSize(maxSize)
    {
        std::filesystem::create_directories(logDirectory);
        logFile.open(GetLogFilePath(), std::ios::app);
    }

    LogHelper::~LogHelper()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    std::string LogHelper::GetLogFilePath()
    {
        std::ostringstream filePath;
        filePath << logDirectory << "/" << baseFileName;

        if (fileSuffix > 0)
        {
            filePath << "_" << fileSuffix;
        }

        filePath << FILE_EXTENSION;
        return filePath.str();
    }

    void LogHelper::LogToFile(const std::string &message)
    {
        std::ifstream file(GetLogFilePath(), std::ios::binary | std::ios::ate);
        if (file.tellg() > maxFileSize)
        {
            fileSuffix++;
            if (logFile.is_open())
            {
                logFile.close();
            }
            logFile.open(GetLogFilePath(), std::ios::app);
        }
        logFile << message << std::endl;
    }
}
