#include "SignalHandler.h"

namespace Core
{

    std::atomic<bool> SignalHandler::isRunning(true);

    void SignalHandler::Initialize()
    {
        std::signal(SIGINT, SignalHandler::HandleSignal);
        std::signal(SIGTERM, SignalHandler::HandleSignal);
    }

    void SignalHandler::HandleSignal(int signal)
    {
        if (signal == SIGINT || signal == SIGTERM)
        {
            isRunning.store(false);
        }
    }
}