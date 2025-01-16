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
        std::atomic<bool> isRunning;
        std::thread serviceThread;

    protected:
        const std::string serviceName;
        std::mutex serviceMutex;
        virtual void Task() = 0;

    public:
        BaseService(const std::string &serviceName);
        virtual ~BaseService();

        void Start();
        void Stop();
        bool IsRunning() const;
        const std::string &GetServiceName() const;
    };
}

#endif
