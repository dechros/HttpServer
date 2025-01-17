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
        constexpr static int TASK_INTERVAL_MS = 100;
        std::queue<std::string> logQueue;

        void Task() override;
        void HandleError(const std::string &methodName, const std::string &message) override;

    public:
        LogService(const std::string &serviceName);
        ~LogService();
        void Log(const std::string &className, const std::string &methodName, const std::string &message);
    };
}

#endif
