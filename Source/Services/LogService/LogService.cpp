#include "LogService.h"
#include "DateTimeUtility.h"
#include "ConsoleUtility.h"
#include "LogFileUtility.h"
#include "LogHelper.h"
#include <filesystem>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <stdexcept>

namespace Services
{
    LogService::LogService(const std::string &serviceName) : BaseService(serviceName)
    {
    }

    LogService::~LogService()
    {
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
            Utilities::ConsoleUtility::Log(logEntry);
            if (!Utilities::LogFileUtility::Log(logEntry))
            {
                HandleError("Task", "Failed to log to file");
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(TASK_INTERVAL_MS));
    }

    void LogService::Log(const std::string &className, const std::string &methodName, const std::string &message)
    {
        std::unique_lock<std::mutex> lock(serviceMutex);
        std::string logEntry = Helpers::LogHelper::FormatLog(className, methodName, message);

        if (logQueue.size() >= MAX_QUEUE_SIZE)
        {
            logQueue.pop();
        }
        logQueue.push(logEntry);
    }

    void LogService::HandleError(const std::string &methodName, const std::string &message)
    {
        if (!HasError())
        {
            Utilities::ConsoleUtility::Log(GetServiceName(), methodName, message);
            error = true;
        }
    }
}
