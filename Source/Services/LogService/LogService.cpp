#include "LogService.h"
#include "DateTimeUtility.h"
#include <filesystem>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <stdexcept>

namespace Services
{
    LogService::LogService(const std::string &serviceName) : BaseService(serviceName), logFileSuffix(0), FILE_BASE_NAME(Utilities::DateTimeUtility::GetCurrentDateTime("_"))
    {
        try
        {
            std::filesystem::create_directories(LOGS_PATH);
            logFile.open(GetLogFileName(), std::ios::app);

            if (!logFile.is_open())
            {
                throw std::runtime_error("Failed to open initial log file: " + GetLogFileName());
            }
        }
        catch (const std::exception &e)
        {
            HandleError("Initialization error: " + std::string(e.what()));
        }
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

        if (HasError())
        {
            try
            {
                std::filesystem::create_directories(LOGS_PATH);

                if (!std::filesystem::exists(GetLogFileName()))
                {
                    logFile.open(GetLogFileName(), std::ios::app);
                    if (!logFile.is_open())
                    {
                        logFileSuffix++;
                        logFile.open(GetLogFileName(), std::ios::app);
                    }
                }
                else
                {
                    logFile.open(GetLogFileName(), std::ios::app);
                }

                if (!logFile.is_open())
                {
                    logFileSuffix++;
                    logFile.open(GetLogFileName(), std::ios::app);
                }

                if (logFile.is_open())
                {
                    error = false;
                }
            }
            catch (const std::exception &e)
            {
                HandleError("LogService encountered an error during file handling: " + std::string(e.what()));
            }

            return;
        }

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
        std::string logEntry = Utilities::DateTimeUtility::GetCurrentTime() + " | " + logServiceName + " | " + message;

        if (HasError())
        {
            std::unique_lock<std::mutex> lock(consoleMutex);
            LogToConsole(logEntry);
            return;
        }

        if (logQueue.size() >= MAX_QUEUE_SIZE)
        {
            logQueue.pop();
        }
        logQueue.push(logEntry);
    }

    std::string LogService::GetLogFileName() const
    {
        std::string fileName = LOGS_PATH + "/" + FILE_BASE_NAME;

        if (logFileSuffix > 0)
        {
            fileName += "_" + std::to_string(logFileSuffix);
        }

        return fileName + FILE_EXTENSION;
    }

    void LogService::LogToFile(const std::string &message)
    {
        try
        {
            int logFileSize = 0;

            if (std::filesystem::exists(GetLogFileName()))
            {
                logFileSize = std::filesystem::file_size(GetLogFileName());
            }

            if (logFileSize > MAX_LOG_SIZE_MB * 1024 * 1024)
            {
                logFileSuffix++;
                if (logFile.is_open())
                {
                    logFile.close();
                }
                logFile.open(GetLogFileName(), std::ios::app);

                if (!logFile.is_open())
                {
                    throw std::runtime_error("Failed to open rotated log file: " + GetLogFileName());
                }
            }

            if (logFile.is_open())
            {
                logFile << message << std::endl;
            }
            else
            {
                throw std::runtime_error("Log file is not open: " + GetLogFileName());
            }
        }
        catch (const std::exception &e)
        {
            HandleError("Error writing to log file: " + std::string(e.what()));
        }
    }

    void LogService::LogToConsole(const std::string &message)
    {
        std::unique_lock<std::mutex> lock(consoleMutex);
        std::cout << message << std::endl;
    }

    void LogService::HandleError(const std::string &errorMessage)
    {
        std::unique_lock<std::mutex> lock(serviceMutex);

        if (!HasError())
        {
            LogToConsole("LogService encountered an error: " + errorMessage);
            error = true;
        }
    }
}
