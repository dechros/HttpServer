#ifndef BASE_SERVICE_H
#define BASE_SERVICE_H

#include <iostream>
#include <string>
#include <thread>
#include <atomic>

namespace Services
{
    class BaseService
    {
    private:
        const std::string serviceName;
        std::atomic<bool> isRunning;
        std::thread serviceThread;

    protected:
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
