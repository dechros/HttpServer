#include "BaseService.h"

namespace Core::Services
{
    BaseService::BaseService(const ServiceConfig &config) : serviceConfig(config), isRunning(false), error(false)
    {
    }

    BaseService::~BaseService()
    {
        if (isRunning.load())
        {
            Stop();
        }
        if (serviceThread.joinable())
        {
            serviceThread.join();
        }
    }

    void BaseService::Start()
    {
        isRunning.store(true);
        serviceThread = std::thread([this]()
                                    {
            while (isRunning.load())
            {
                Task();
            } });
    }

    void BaseService::Stop()
    {
        isRunning.store(false);
        if (serviceThread.joinable())
        {
            serviceThread.join();
        }
    }

    bool BaseService::IsRunning() const
    {
        return isRunning.load();
    }

    bool BaseService::HasError() const
    {
        return error.load();
    }

    const std::string &BaseService::GetServiceName() const
    {
        return serviceConfig.GetServiceName();
    }
}
