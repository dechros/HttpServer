#ifndef SOCKET_UTILITY_H
#define SOCKET_UTILITY_H

#include <string>
#include <stdexcept>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include "TcpClient.h"

namespace Core::Utilities
{

    class SocketUtility
    {
    private:
        constexpr static int BUFFER_SIZE = 4096;
        int serverSocket;
        bool initialized;

    public:
        SocketUtility();
        ~SocketUtility();

        void BindAndListen(int port, int maxClients, bool nonBlocking = true);
        Types::TcpClient AcceptConnection();
        std::string Receive(Types::TcpClient client);
        void Send(Types::TcpClient client, const std::string &message);
        void CloseSocket(int socket);
        void CloseServerSocket();
    };
}

#endif
