#ifndef ERROR_SERVICE_H
#define ERROR_SERVICE_H

#include "BaseService.h"
#include <queue>
#include <string>
#include <mutex>

namespace Services
{
    class ErrorService : public BaseService
    {
    private:
        std::queue<std::string> errorQueue;
        constexpr static int MAX_QUEUE_SIZE = 10;

        void Task() override;

    public:
        ErrorService(const std::string &serviceName);
        ~ErrorService();
        void LogError(const std::string &error, const std::string &logServiceName);
    };
}

#endif