#include "LogService.h"
#include "DateTimeHelper.h"
#include "LogConsoleUtility.h"
#include "LogFileUtility.h"
#include <filesystem>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <stdexcept>

namespace Core::Services
{
    LogService::LogService(const std::string &serviceName, std::unordered_map<std::string, std::string> &args) : BaseService(serviceName, args)
    {
        HandleError("Failed to start log service", "Task");
    }

    LogService::~LogService()
    {
    }

    void LogService::Task()
    {

        {
            std::unique_lock<std::mutex> lock(serviceMutex);

            if (!logQueue.empty())
            {
                Core::Types::LogEntry logEntry = logQueue.front();
                Core::Utilities::LogConsoleUtility::Log(logEntry);
                if (!Core::Utilities::LogFileUtility::Log(logEntry))
                {
                    HandleError("Failed to log to file", "Task");
                }
                logQueue.pop();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(TASK_INTERVAL_MS));
    }

    void LogService::AddLog(const Core::Types::LogEntry &logEntry)
    {
        std::unique_lock<std::mutex> lock(serviceMutex);

        if (logQueue.size() >= MAX_QUEUE_SIZE)
        {
            logQueue.pop();
        }
        logQueue.push(logEntry);
    }

    void LogService::HandleError(const std::string &message, const std::string &methodName)
    {
        if (!HasError())
        {
            Utilities::LogConsoleUtility::Log(Core::Types::LogEntry(message, "LogService", methodName));
            error = true;
        }
    }
}
