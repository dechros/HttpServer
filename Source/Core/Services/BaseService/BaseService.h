#ifndef BASE_SERVICE_H
#define BASE_SERVICE_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <variant>
#include "ServiceConfig.h"

namespace Core::Services
{
    class BaseService
    {
    private:
        std::atomic<bool> isRunning;
        std::thread serviceThread;
        std::string serviceName;

    protected:
        const ServiceConfig serviceConfig;
        std::atomic<bool> error;
        std::mutex serviceMutex;

        virtual void Task() = 0;
        virtual void HandleError(const std::string &message, const std::string &methodName) = 0;

    public:
        BaseService(int numArgs, char *argArray[], const std::string &serviceName);
        virtual ~BaseService();

        void Start();
        void Stop();
        bool IsRunning() const;
        bool HasError() const;
        const std::string &GetServiceName() const;
    };
}

#endif
