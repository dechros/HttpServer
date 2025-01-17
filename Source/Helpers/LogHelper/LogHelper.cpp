#include "LogHelper.h"
#include "DateTimeUtility.h"

namespace Helpers
{
    std::string LogHelper::FormatLog(const std::string &className, const std::string &methodName, const std::string &message)
    {
        std::string currentDateTime = Utilities::DateTimeUtility::GetCurrentDateTime();
        std::string formattedLog = "[" + currentDateTime + "] [" + className + "::" + methodName + "] " + message;

        return formattedLog;
    }
}
