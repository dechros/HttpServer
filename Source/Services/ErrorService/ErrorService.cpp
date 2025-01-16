#include "ErrorService.h"
#include "DateTimeHelper.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>

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
        std::this_thread::sleep_for(std::chrono::milliseconds(TASK_INTERVAL_MS));
    }

    void ErrorService::LogError(const std::string &error, const std::string &logServiceName)
    {
        std::unique_lock<std::mutex> lock(serviceMutex);
        std::string dateTimeString = Helpers::DateTimeHelper::GetCurrentDateTime();

        if (errorQueue.size() >= MAX_QUEUE_SIZE)
        {
            errorQueue.pop();
            errorQueue.pop();
            errorQueue.push(dateTimeString + " | " + serviceName + " | " + "Please increase max queue size.");
        }
        errorQueue.push(dateTimeString + " | " + logServiceName + " | " + error);
    }
}
