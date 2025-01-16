#include "ErrorService.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace Services
{
    ErrorService::ErrorService(const std::string &serviceName) : BaseService(serviceName)
    {
    }

    ErrorService::~ErrorService()
    {
    }

    void ErrorService::Task()
    {
        if (!errorQueue.empty())
        {
            std::cout << errorQueue.front() << std::endl;
            errorQueue.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void ErrorService::LogError(const std::string &error, const std::string &logServiceName)
    {
        std::unique_lock<std::mutex> lock(serviceMutex);
        if (errorQueue.size() >= MAX_QUEUE_SIZE)
        {
            errorQueue.pop();
            errorQueue.pop();
            errorQueue.push(serviceName + ": " + "Please increase max queue size in Error Service.");
        }
        errorQueue.push(logServiceName + ": " + error);
    }
}
