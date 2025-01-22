#include "LogFileUtility.h"
#include "DateTimeHelper.h"
#include "FileHelper.h"
#include <mutex>

namespace Core::Utilities
{
    int LogFileUtility::logFileSuffix = 0;
    std::mutex LogFileUtility::logFileMutex;
    const std::string LogFileUtility::FILE_BASE_NAME = Helpers::DateTimeHelper::GetCurrentDateTime("_");

    void LogFileUtility::Log(const Types::LogEntry &logEntry)
    {
        std::unique_lock<std::mutex> lock(logFileMutex);

        int fileSize = Helpers::FileHelper::GetFileSizeInMB(GetLogFileName());
        if (fileSize >= MAX_LOG_SIZE_MB)
        {
            logFileSuffix++;
        }

        Helpers::FileHelper::AppendToFile(GetLogFileName(), logEntry.GetFormattedLog());
    }

    std::string LogFileUtility::GetLogFileName()
    {
        std::string fileName = LOGS_PATH + "/" + FILE_BASE_NAME;

        if (logFileSuffix > 0)
        {
            fileName += "_" + std::to_string(logFileSuffix);
        }

        return fileName + FILE_EXTENSION;
    }
}