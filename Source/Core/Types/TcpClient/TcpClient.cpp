#include "TcpClient.h"

namespace Core::Types
{
    TcpClient::TcpClient(int socket) : socket(socket), lastActivity(std::chrono::steady_clock::now())
    {
    }

    TcpClient::~TcpClient()
    {
    }

    void TcpClient::UpdateActivity()
    {
        lastActivity = std::chrono::steady_clock::now();
    }

    bool TcpClient::IsTimeout(int timeoutMilliseconds) const
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastActivity).count();
        return elapsed >= timeoutMilliseconds;
    }

    int TcpClient::GetSocket() const
    {
        return socket;
    }

    bool TcpClient::operator==(const TcpClient &other) const
    {
        return socket == other.socket;
    }
}
