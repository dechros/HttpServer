#include "Server.h"
#include "LogService.h"
#include "SignalHandler.h"

namespace Core
{
    Server::Server(int numArgs, char *argArray[])
    {
        Core::SignalHandler::Initialize();
        serviceRegistry.RegisterService(std::make_shared<Services::LogService>(Services::ServiceConfig(numArgs, argArray, "LogService")));
    }

    Server::~Server()
    {
    }

    void Server::Run()
    {
        serviceRegistry.StartAll();
        while (!serviceRegistry.HasError() && Core::SignalHandler::isRunning.load())
        {
            auto logService = std::dynamic_pointer_cast<Services::LogService>(*serviceRegistry.GetService("LogService"));
            if (logService)
            {
                logService->AddLog(Core::Types::LogEntry("Server is running", "Server", "Run"));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        serviceRegistry.StopAll();
    }
}