#ifndef BASE_SERVICE_H
#define BASE_SERVICE_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <atomic>
#include "ServiceConfig.h"

namespace Core::Services
{
    class BaseService
    {
    private:
        const ServiceConfig serviceConfig;
        std::atomic<bool> isRunning;
        std::thread serviceThread;

    protected:
        std::atomic<bool> error;
        std::mutex serviceMutex;

        virtual void Task() = 0;
        virtual void HandleError(const std::string &message, const std::string &methodName) = 0;

    public:
        BaseService(const ServiceConfig &config);
        virtual ~BaseService();

        const std::string &GetServiceName() const;
        void Start();
        void Stop();
        bool IsRunning() const;
        bool HasError() const;
    };
}

#endif
