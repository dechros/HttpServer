#include "Server.h"
#include "LogService.h"
#include "CommunicationService.h"
#include "SignalHandler.h"

namespace Core
{
    Server::Server(int numArgs, char *argArray[])
    {
        SignalHandler::Initialize();

        auto logServicePtr = std::make_shared<Services::LogService>(Services::ServiceConfig(numArgs, argArray, "LogService"));
        serviceRegistry.RegisterService(logServicePtr);

        auto logService = std::dynamic_pointer_cast<Services::LogService>(serviceRegistry.GetService("LogService"));
        serviceRegistry.RegisterService(std::make_shared<Services::CommunicationService>(Services::ServiceConfig(numArgs, argArray, "CommunicationService"), *logService));
    }

    Server::~Server()
    {
    }

    void Server::Run()
    {
        serviceRegistry.StartAll();
        while (!serviceRegistry.HasError() && SignalHandler::isRunning.load())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        serviceRegistry.StopAll();
    }
}