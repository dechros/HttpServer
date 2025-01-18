#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include <string>

namespace Core::Types
{
    class LogEntry
    {
    private:
        const std::string currentDateTime;
        const std::string message;
        const std::string className;
        const std::string methodName;

    public:
        LogEntry(const std::string &message, const std::string &className = "", const std::string &methodName = "");
        ~LogEntry();
        const std::string GetFormattedLog() const;
    };
}

#endif