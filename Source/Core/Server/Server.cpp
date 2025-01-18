#include "Server.h"
#include "LogService.h"

namespace Core
{
    Server::Server(int numArgs, char *argArray[])
    {
        serviceArgs["arg1"] = "value1";
        serviceArgs["arg2"] = "value2";

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