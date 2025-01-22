#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

#include "BaseService.h"
#include "LogService.h"
#include "SocketUtility.h"
#include "TcpClient.h"
#include <memory>
#include <unordered_set>
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

namespace Core::Services
{
    class CommunicationService : public BaseService
    {
    private:
        constexpr static int DEFAULT_PORT = 8080;
        constexpr static int MAX_CLIENTS = 100;
        int serverPort;
        LogService &logService;
        Utilities::SocketUtility socketUtility;
        std::vector<Types::TcpClient> clients;

        void HandleClient(Types::TcpClient client);

    protected:
        void Task() override;

    public:
        CommunicationService(const ServiceConfig &config, LogService &logService);
        ~CommunicationService();
    };
}

#endif
