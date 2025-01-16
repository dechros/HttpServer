#ifndef ERROR_SERVICE_H
#define ERROR_SERVICE_H

#include "BaseService.h"
#include <queue>
#include <string>

namespace Services
{
    class ErrorService : public BaseService
    {
    private:
        constexpr static int MAX_QUEUE_SIZE = 100;
        constexpr static int MAX_LOG_SIZE_MB = 100;
        constexpr static int TASK_INTERVAL_MS = 100;
        constexpr static std::string LOGS_PATH = "./Logs/";
        std::queue<std::string> errorQueue;

        void Task() override;

    public:
        ErrorService(const std::string &serviceName);
        ~ErrorService();
        void LogError(const std::string &error, const std::string &logServiceName);
    };
}

#endif
