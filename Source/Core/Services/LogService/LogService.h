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

    public:
        LogService(const ServiceConfig &config);
        ~LogService();
        void AddLog(const Core::Types::LogEntry &logEntry);
    };
}

#endif
