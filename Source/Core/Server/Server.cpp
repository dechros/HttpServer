#include "Server.h"
#include "LogService.h"

namespace Core
{
    Server::Server(int numArgs, char *argArray[])
    {
        for (int i = 1; i < numArgs; i++)
        {
            std::string key = argArray[i];
            if (i + 1 < numArgs && argArray[i + 1][0] != '-')
            {
                std::string value = argArray[i + 1];
                std::cout << key << ": " << value << std::endl;
                serviceArgs[key] = value;
                i++;                     
            }
            else
            {
                serviceArgs[key] = "";
            }
        } // --key value

        auto service = std::make_shared<Core::Services::LogService>("LogService", serviceArgs);
        serviceRegistry.RegisterService(service);
    }

    Server::~Server()
    {
    }

    void Server::Run()
    {
        serviceRegistry.StartAll();
    }
}