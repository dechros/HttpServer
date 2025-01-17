#ifndef BASE_SERVICE_H
#define BASE_SERVICE_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

namespace Services
{
    class BaseService
    {
    private:
        const std::string serviceName;
        std::atomic<bool> isRunning;
        std::thread serviceThread;

    protected:
        std::atomic<bool> error;
        std::mutex serviceMutex;
        virtual void Task() = 0;
        virtual void HandleError(const std::string &errorMessage) = 0;

    public:
        BaseService(const std::string &serviceName);
        virtual ~BaseService();

        void Start();
        void Stop();
        bool IsRunning() const;
        bool HasError() const;
        const std::string &GetServiceName() const;
    };
}

#endif
