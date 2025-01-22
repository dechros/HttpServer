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
        AddLog({"Starting LogService", GetServiceName(), "Constructor"});
    }

    LogService::~LogService()
    {
        AddLog({"Stopping LogService", GetServiceName(), "Destructor"});
    }

    void LogService::Task()
    {
        {
            std::unique_lock<std::mutex> lock(serviceMutex);

            if (!logQueue.empty())
            {
                Types::LogEntry logEntry = logQueue.front();
                Utilities::LogConsoleUtility::Log(logEntry);
                try
                {
                    Utilities::LogFileUtility::Log(logEntry);
                }
                catch (const std::exception &e)
                {
                    Utilities::LogConsoleUtility::Log({"Error logging to file: " + std::string(e.what()), GetServiceName(), "Task"});
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
            Utilities::LogConsoleUtility::Log({"Log queue full. Please increase MAX_QUEUE_SIZE", GetServiceName(), "AddLog"});
            logQueue.pop();
        }
        logQueue.push(logEntry);
    }
}
