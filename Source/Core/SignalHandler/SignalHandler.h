#include <csignal>
#include <atomic>
#include <iostream>

namespace Core
{
    class SignalHandler
    {
    public:
        static std::atomic<bool> isRunning;
        static void Initialize();
        static void HandleSignal(int signal);
    };
}
