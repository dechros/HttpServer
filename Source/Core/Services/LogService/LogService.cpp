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
    LogService::LogService(const ServiceConfig &config) : BaseService(config)
    {
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
                Types::LogEntry logEntry = logQueue.front();
                Utilities::LogConsoleUtility::Log(logEntry);
                if (!Utilities::LogFileUtility::Log(logEntry))
                {
                    Utilities::LogConsoleUtility::Log({"Failed to log to file: " + Utilities::LogFileUtility::GetLogFileName(), GetServiceName(), "Task"});
                }
                logQueue.pop();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(TASK_INTERVAL_MS));
    }

    void LogService::AddLog(const Types::LogEntry &logEntry)
    {
        std::unique_lock<std::mutex> lock(serviceMutex);

        if (logQueue.size() >= MAX_QUEUE_SIZE)
        {
            logQueue.pop();
        }
        logQueue.push(logEntry);
    }
}
