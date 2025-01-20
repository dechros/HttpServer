#include "ServiceConfig.h"

namespace Core::Services
{
    ServiceConfig::ServiceConfig(int argc, char *argv[], const std::string &serviceName) : serviceName(serviceName), args(ParseArgs(argc, argv))
    {
    }

    ServiceConfig::~ServiceConfig()
    {
    }

    std::string ServiceConfig::Get(const std::string &key) const
    {
        auto it = args.find(key);
        return it != args.end() ? it->second : "";
    }

    bool ServiceConfig::Has(const std::string &key) const
    {
        return args.find(key) != args.end();
    }

    std::unordered_map<std::string, std::string> ServiceConfig::ParseArgs(int argc, char *argv[])
    {
        std::unordered_map<std::string, std::string> args;
        for (int i = 1; i < argc; ++i)
        {
            std::string key = argv[i];
            if (key.rfind("--", 0) != 0)
            {
                continue;
            }
            if (i + 1 < argc && argv[i + 1][0] != '-')
            {
                args[key] = argv[i + 1];
                ++i;
            }
            else
            {
                args[key] = "";
            }
        }
        return args;
    }

    const std::string &ServiceConfig::GetServiceName() const
    {
        return serviceName;
    }
}