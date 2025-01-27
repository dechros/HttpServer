#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <chrono>

namespace Core::Types
{
    class TcpClient
    {
    private:
        int socket;
        std::chrono::steady_clock::time_point lastActivity;

    public:
        TcpClient(int socket);
        ~TcpClient();
        void UpdateActivity();
        bool IsTimeout(int timeoutMilliseconds) const;
        int GetSocket() const;
        bool operator==(const TcpClient &other) const;
    };
}

#endif