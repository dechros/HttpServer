#include "LogEntry.h"
#include "DateTimeHelper.h"

namespace Core::Types
{
    LogEntry::LogEntry(const std::string &message, const std::string &className, const std::string &methodName) : message(message), className(className), methodName(methodName), currentDateTime(Helpers::DateTimeHelper::GetCurrentDateTime())
    {
    }

    LogEntry::~LogEntry()
    {
    }

    const std::string LogEntry::GetFormattedLog() const
    {
        std::string formattedLog;

        if (className.empty() || methodName.empty())
        {
            formattedLog = message;
        }
        else
        {
            std::string currentDateTime = Helpers::DateTimeHelper::GetCurrentDateTime();
            formattedLog = "[" + currentDateTime + "] [" + className + "::" + methodName + "] " + message;
        }

        return formattedLog;
    }
}