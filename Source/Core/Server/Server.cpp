#include "Server.h"
#include "LogService.h"

namespace Core
{
    Server::Server(int numArgs, char *argArray[])
    {
        auto service = std::make_shared<Core::Services::LogService>(numArgs, argArray, "LogService");
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