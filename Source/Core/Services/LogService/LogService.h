#ifndef LOG_SERVICE_H
#define LOG_SERVICE_H

#include "BaseService.h"
#include "LogEntry.h"
#include <queue>
#include <string>
#include <fstream>
#include <mutex>

namespace Core::Services
{
    class LogService : public BaseService
    {
    private:
        constexpr static int MAX_QUEUE_SIZE = 100;
        constexpr static int TASK_INTERVAL_MS = 100;
        std::queue<Core::Types::LogEntry> logQueue;

        void Task() override;
        void HandleError(const std::string &message, const std::string &methodName) override;

    public:
        LogService(int numArgs, char *argArray[], const std::string &serviceName);
        ~LogService();
        void AddLog(const Core::Types::LogEntry &logEntry);
    };
}

#endif
