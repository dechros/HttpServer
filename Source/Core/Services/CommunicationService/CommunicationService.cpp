#include "CommunicationService.h"
#include <thread>
#include <algorithm>

namespace Core::Services
{
    CommunicationService::CommunicationService(const ServiceConfig &config, std::shared_ptr<LogService> logService) : BaseService(config), logService(logService)
    {
        logService->AddLog({"Starting CommunicationService", "CommunicationService", "Constructor"});
        try
        {
            serverPort = std::stoi(serviceConfig.Get("port"));
        }
        catch (const std::exception &e)
        {
            logService->AddLog({"Error parsing port: " + std::string(e.what()), "CommunicationService", "Constructor"});
            serverPort = 8080;
        }
        try
        {
            socketUtility.BindAndListen(serverPort, MAX_CLIENTS);
        }
        catch (const std::exception &e)
        {
            logService->AddLog({"Error during BindAndListen: " + std::string(e.what()), "CommunicationService", "Constructor"});
            error = true;
        }
    }

    CommunicationService::~CommunicationService()
    {
        logService->AddLog({"Stopping CommunicationService", "CommunicationService", "Destructor"});
        for (auto &client : clients)
        {
            try
            {
                socketUtility.CloseSocket(client.GetSocket());
            }
            catch (const std::exception &e)
            {
                logService->AddLog({"Error closing client socket" + std::to_string(client.GetSocket()) + ": " + std::string(e.what()), "CommunicationService", "Destructor"});
            }
        }
        socketUtility.CloseServerSocket();
    }

    void CommunicationService::HandleClient(Types::TcpClient client)
    {
        try
        {
            std::string message = socketUtility.Receive(client);
            if (message.empty())
            {
                logService->AddLog({"Client disconnected", "CommunicationService", "HandleClient"});
                socketUtility.CloseSocket(client.GetSocket());
                clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
                return;
            }
            logService->AddLog({"Received message: " + message, "CommunicationService", "HandleClient"});
            socketUtility.Send(client.GetSocket(), "Echo: " + message);
            logService->AddLog({"Sent response", "CommunicationService", "HandleClient"});
        }
        catch (const std::exception &e)
        {
            logService->AddLog({"Error handling client: " + std::string(e.what()), "CommunicationService", "HandleClient"});
            socketUtility.CloseSocket(client.GetSocket());
            clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
        }
    }

    void CommunicationService::Task()
    {
        Types::TcpClient client(-1);
        try
        {
            client = socketUtility.AcceptConnection();
            logService->AddLog({"Client connected", "CommunicationService", "Task"});
            if (clients.size() >= MAX_CLIENTS)
            {
                socketUtility.CloseSocket(client.GetSocket());
                logService->AddLog({"Max clients reached", "CommunicationService", "Task"});
                return;
            }
            if (std::find(clients.begin(), clients.end(), client) != clients.end())
            {
                socketUtility.CloseSocket(client.GetSocket());
                logService->AddLog({"Client already connected", "CommunicationService", "Task"});
                return;
            }
            clients.push_back(client);
            std::thread(&CommunicationService::HandleClient, this, client).detach();
        }
        catch (const std::exception &e)
        {
            logService->AddLog({"Error during client acceptance or task execution: " + std::string(e.what()), "CommunicationService", "Task"});
            if (client.GetSocket() != -1)
            {
                socketUtility.CloseSocket(client.GetSocket());
                clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
            }
        }
    }
}
