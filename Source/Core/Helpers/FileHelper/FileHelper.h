#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <string>
#include <fstream>

namespace Core::Helpers
{
    class FileHelper
    {
    public:
        static std::string ReadFile(const std::string &filePath);
        static bool AppendToFile(const std::string &filePath, const std::string &content);
        static bool WriteToFile(const std::string &filePath, const std::string &content);
        static int GetFileSizeInMB(const std::string &filePath);

    private:
        static bool EnsurePathAndFileExists(const std::string &filePath);
    };
}

#endif
