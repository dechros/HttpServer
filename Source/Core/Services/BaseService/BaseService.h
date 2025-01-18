#ifndef BASE_SERVICE_H
#define BASE_SERVICE_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <variant>

namespace Core::Services
{
    class BaseService
    {
    private:
        const std::string serviceName;
        std::atomic<bool> isRunning;
        std::thread serviceThread;

    protected:
        const std::unordered_map<std::string, std::string> serviceArgs;
        std::atomic<bool> error;
        std::mutex serviceMutex;
        virtual void Task() = 0;
        virtual void HandleError(const std::string &message, const std::string &methodName) = 0;
        const std::string GetArgValue(const std::string &key) const;

    public:
        BaseService(const std::string &serviceName, std::unordered_map<std::string, std::string> &args);
        virtual ~BaseService();

        void Start();
        void Stop();
        bool IsRunning() const;
        bool HasError() const;
        const std::string &GetServiceName() const;
    };
}

#endif
