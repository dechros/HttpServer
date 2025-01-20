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
        const std::unordered_map<std::string, std::string> args;
        std::unordered_map<std::string, std::string> ParseArgs(int argc, char *argv[]);

    public:
        ServiceConfig(int argc, char *argv[]);
        ~ServiceConfig();
        std::string Get(const std::string &key) const;
        bool Has(const std::string &key) const;
    };
}

#endif
