#ifndef SERVICE_REGISTRY_H
#define SERVICE_REGISTRY_H

#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>
#include "BaseService.h"

namespace Core::Services
{
    class ServiceRegistry
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<BaseService>> services;

    public:
        ServiceRegistry();
        ~ServiceRegistry();
        void RegisterService(const std::shared_ptr<BaseService> &service);
        std::shared_ptr<BaseService> GetService(const std::string &name);

        void StartAll();
        void StopAll();
        bool HasError() const;
    };
}

#endif
