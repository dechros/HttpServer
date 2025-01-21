#include "SocketUtility.h"
#include <cstring>
#include <stdexcept>

namespace Core::Utilities
{
    SocketUtility::SocketUtility() : serverSocket(-1), initialized(false)
    {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            throw std::runtime_error("Failed to initialize WinSock");
        }
#endif
        initialized = true;
    }

    SocketUtility::~SocketUtility()
    {
        if (serverSocket >= 0)
        {
            CloseSocket(serverSocket);
        }
#ifdef _WIN32
        if (initialized)
        {
            WSACleanup();
        }
#endif
    }

    void SocketUtility::BindAndListen(int port, int maxClients, bool nonBlocking)
    {
        if (!initialized)
        {
            throw std::runtime_error("SocketUtility not initialized");
        }

        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0)
        {
            throw std::runtime_error("Failed to create socket");
        }

        if (nonBlocking)
        {
#ifdef _WIN32
            u_long mode = 1;
            if (ioctlsocket(serverSocket, FIONBIO, &mode) != 0)
#else
            if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) < 0)
#endif
            {
                CloseSocket(serverSocket);
                throw std::runtime_error("Failed to set socket to non-blocking mode");
            }
        }

        sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        {
            CloseSocket(serverSocket);
            throw std::runtime_error("Failed to bind socket");
        }

        if (listen(serverSocket, maxClients) < 0)
        {
            CloseSocket(serverSocket);
            throw std::runtime_error("Failed to listen on socket");
        }
    }

    Types::TcpClient SocketUtility::AcceptConnection()
    {
        if (!initialized || serverSocket < 0)
        {
            throw std::runtime_error("Server socket not initialized or invalid");
        }

        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
        if (clientSocket < 0)
        {
#ifdef _WIN32
            if (WSAGetLastError() != WSAEWOULDBLOCK)
#else
            if (errno != EAGAIN && errno != EWOULDBLOCK)
#endif
            {
                throw std::runtime_error("Error accepting client connection");
            }
        }

        return Types::TcpClient(clientSocket);
    }

    std::string SocketUtility::Receive(Types::TcpClient client)
    {
        if (!initialized || client.GetSocket() < 0)
        {
            throw std::runtime_error("SocketUtility not initialized or invalid client socket");
        }

        std::string message;
        char buffer[BUFFER_SIZE];

        while (true)
        {
            int bytesRead = recv(client.GetSocket(), buffer, BUFFER_SIZE, 0);

            if (bytesRead < 0)
            {
#ifdef _WIN32
                if (WSAGetLastError() == WSAEWOULDBLOCK)
#else
                if (errno == EAGAIN || errno == EWOULDBLOCK)
#endif
                {
                    break;
                }
                throw std::runtime_error("Error receiving data");
            }

            if (bytesRead == 0)
            {
                break;
            }

            message.append(buffer, bytesRead);
            client.UpdateActivity();
        }

        return message;
    }

    void SocketUtility::Send(Types::TcpClient client, const std::string &message)
    {
        if (!initialized || client.GetSocket() < 0)
        {
            throw std::runtime_error("SocketUtility not initialized or invalid client socket");
        }

        if (send(client.GetSocket(), message.c_str(), message.size(), 0) < 0)
        {
            throw std::runtime_error("Failed to send data");
        }

        client.UpdateActivity();
    }

    void SocketUtility::CloseSocket(int socket)
    {
#ifdef _WIN32
        if (closesocket(socket) < 0)
#else
        if (close(socket) < 0)
#endif
        {
            throw std::runtime_error("Failed to close socket");
        }
    }

    void SocketUtility::CloseServerSocket()
    {
        if (serverSocket < 0)
        {
            throw std::runtime_error("Server socket not initialized");
        }

        CloseSocket(serverSocket);
    }
}
