#ifndef SERVICE_CONFIG_H
#define SERVICE_CONFIG_H

#include <string>
#include <unordered_map>
#include <stdexcept>

namespace Core::Services
{
    class ServiceConfig
    {
    private:
        const std::string serviceName;
        const std::unordered_map<std::string, std::string> args;
        std::unordered_map<std::string, std::string> ParseArgs(int argc, char *argv[]);

    public:
        ServiceConfig(int argc, char *argv[], const std::string &serviceName);
        ~ServiceConfig();
        const std::string &GetServiceName() const;
        std::string Get(const std::string &key) const;
        bool Has(const std::string &key) const;
    };
}

#endif
