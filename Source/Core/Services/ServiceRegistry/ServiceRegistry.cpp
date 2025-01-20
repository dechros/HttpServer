#include "ServiceRegistry.h"

namespace Core::Services
{
    ServiceRegistry::ServiceRegistry()
    {
    }

    ServiceRegistry::~ServiceRegistry()
    {
    }

    void ServiceRegistry::RegisterService(const std::shared_ptr<BaseService> &service)
    {
        const std::string &name = service->GetServiceName();

        if (services.find(name) != services.end())
        {
            return;
        }

        services[name] = service;
    }

    std::optional<std::shared_ptr<BaseService>> ServiceRegistry::GetService(const std::string &name)
    {
        auto it = services.find(name);
        if (it == services.end())
        {
            return std::nullopt;
        }

        return it->second;
    }

    void ServiceRegistry::StartAll()
    {
        for (auto &[name, service] : services)
        {
            service->Start();
        }
    }

    void ServiceRegistry::StopAll()
    {
        for (auto &[name, service] : services)
        {
            service->Stop();
        }
    }

    bool ServiceRegistry::HasError() const
    {
        for (const auto &[name, service] : services)
        {
            if (service->HasError())
            {
                return true;
            }
        }
        return false;
    }
}