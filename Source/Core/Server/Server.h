#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <csignal>
#include <atomic>
#include "ServiceRegistry.h"
#include "LogService.h"

namespace Core
{
    class Server
    {
    private:
        Services::ServiceRegistry serviceRegistry;

    public:
        Server(int numArgs, char *argArray[]);
        ~Server();
        void Run();
    };
}

#endif