#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include "ServiceRegistry.h"

namespace Core
{
    class Server
    {
    private:
        Core::Services::ServiceRegistry serviceRegistry;
        std::unordered_map<std::string, std::string> serviceArgs;

    public:
        Server(int numArgs, char *argArray[]);
        ~Server();
        void Run();
    };
}

#endif