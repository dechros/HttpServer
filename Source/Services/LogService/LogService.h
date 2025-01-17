#ifndef LOG_SERVICE_H
#define LOG_SERVICE_H

#include "BaseService.h"
#include <queue>
#include <string>
#include <fstream>
#include <mutex>

namespace Services
{
    class LogService : public BaseService
    {
    private:
        constexpr static int MAX_QUEUE_SIZE = 100;
        constexpr static int MAX_LOG_SIZE_MB = 100;
        constexpr static int TASK_INTERVAL_MS = 100;
        constexpr static std::string FILE_EXTENSION = ".txt";
        constexpr static std::string LOGS_PATH = "./Logs";
        const std::string FILE_BASE_NAME;
        int logFileSuffix;
        std::fstream logFile;
        std::queue<std::string> logQueue;
        std::mutex consoleMutex;

        void Task() override;
        void LogToFile(const std::string &message);
        void LogToConsole(const std::string &message);
        std::string GetLogFileName() const;
        void HandleError(const std::string &errorMessage) override;

    public:
        LogService(const std::string &serviceName);
        ~LogService();
        void Log(const std::string &message, const std::string &logServiceName);
    };
}

#endif
