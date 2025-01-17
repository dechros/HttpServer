#include "LogFileUtility.h"
#include "LogHelper.h"
#include "FileHelper.h"
#include "DateTimeUtility.h"
#include <mutex>

namespace Utilities
{
    int LogFileUtility::logFileSuffix = 0;
    std::mutex LogFileUtility::logFileMutex;
    const std::string LogFileUtility::FILE_BASE_NAME = Utilities::DateTimeUtility::GetCurrentDateTime("_");

    bool LogFileUtility::Log(const std::string &className, const std::string &methodName, const std::string &message)
    {
        std::unique_lock<std::mutex> lock(logFileMutex);

        int fileSize = Helpers::FileHelper::GetFileSizeInMB(GetLogFileName());
        if (fileSize < 0)
        {
            return false;
        }
        if (fileSize >= MAX_LOG_SIZE_MB)
        {
            logFileSuffix++;
        }

        if (!Helpers::FileHelper::AppendToFile(GetLogFileName(), Helpers::LogHelper::FormatLog(className, methodName, message)))
        {
            return false;
        }

        return true;
    }

    bool LogFileUtility::Log(const std::string &message)
    {
        std::unique_lock<std::mutex> lock(logFileMutex);

        int fileSize = Helpers::FileHelper::GetFileSizeInMB(GetLogFileName());
        if (fileSize < 0)
        {
            return false;
        }
        if (fileSize >= MAX_LOG_SIZE_MB)
        {
            logFileSuffix++;
        }

        if (!Helpers::FileHelper::AppendToFile(GetLogFileName(), message))
        {
            return false;
        }

        return true;
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