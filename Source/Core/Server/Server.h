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
        Services::ServiceRegistry serviceRegistry;

    public:
        Server(int numArgs, char *argArray[]);
        ~Server();
        void Run();
    };
}

#endif