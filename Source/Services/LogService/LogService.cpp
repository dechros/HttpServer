#include "LogService.h"
#include "DateTimeHelper.h"
#include <filesystem>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>

namespace Services
{
    LogService::LogService(const std::string &serviceName) : BaseService(serviceName), logFileSuffix(0), LOG_FILE_BASE_NAME(Helpers::DateTimeHelper::GetCurrentDateTimeUnderline())
    {
        std::filesystem::create_directories(LOGS_PATH);
        logFile.open(GetLogFileName(), std::ios::app);
    }

    LogService::~LogService()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void LogService::Task()
    {
        std::string logEntry;
        {
            std::unique_lock<std::mutex> lock(serviceMutex);
            if (!logQueue.empty())
            {
                logEntry = logQueue.front();
                logQueue.pop();
            }
        }

        if (!logEntry.empty())
        {
            LogToConsole(logEntry);
            LogToFile(logEntry);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(TASK_INTERVAL_MS));
    }

    void LogService::Log(const std::string &message, const std::string &logServiceName)
    {
        std::unique_lock<std::mutex> lock(serviceMutex);
        std::ostringstream logStream;
        logStream << Helpers::DateTimeHelper::GetCurrentTime() << " | " << logServiceName << " | " << message;

        if (logQueue.size() >= MAX_QUEUE_SIZE)
        {
            logQueue.pop();
        }
        logQueue.push(logStream.str());
    }

    std::string LogService::GetLogFileName()
    {
        std::string fileName = LOGS_PATH + "/" + LOG_FILE_BASE_NAME;

        if (logFileSuffix > 0)
        {
            fileName += "_" + std::to_string(logFileSuffix);
        }

        return fileName + LOG_FILE_EXTENSION;
    }

    void LogService::LogToFile(const std::string &message)
    {
        int logFileSize = std::filesystem::file_size(GetLogFileName());
        if (logFileSize > MAX_LOG_SIZE_MB * 1024 * 1024)
        {
            logFileSuffix++;
            if (logFile.is_open())
            {
                logFile.close();
            }
            logFile.open(GetLogFileName(), std::ios::app);
        }
        logFile << message << std::endl;
    }

    void LogService::LogToConsole(const std::string &message)
    {
        std::cout << message << std::endl;
    }
}
