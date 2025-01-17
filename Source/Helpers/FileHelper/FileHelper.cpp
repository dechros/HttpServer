#include "FileHelper.h"
#include <filesystem>
#include <sstream>
#include <fstream>

namespace Helpers
{
    std::string FileHelper::ReadFile(const std::string &filePath)
    {
        try
        {
            if (!EnsurePathAndFileExists(filePath))
            {
                return "";
            }

            std::stringstream content;
            std::ifstream file(filePath);

            if (!file.is_open())
            {
                return "";
            }

            content << file.rdbuf();
            file.close();
            return content.str();
        }
        catch (...)
        {
            return "";
        }
    }

    bool FileHelper::AppendToFile(const std::string &filePath, const std::string &content)
    {
        try
        {
            if (!EnsurePathAndFileExists(filePath))
            {
                return false;
            }

            std::ofstream file(filePath, std::ios::app);
            if (!file.is_open())
            {
                return false;
            }

            file << content << std::endl;
            file.close();
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool FileHelper::WriteToFile(const std::string &filePath, const std::string &content)
    {
        try
        {
            if (!EnsurePathAndFileExists(filePath))
            {
                return false;
            }

            std::ofstream file(filePath);

            if (!file.is_open())
            {
                return false;
            }

            file << content;
            file.close();
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    int FileHelper::GetFileSizeInMB(const std::string &filePath)
    {
        try
        {
            if (!EnsurePathAndFileExists(filePath))
            {
                return -1;
            }

            return static_cast<int>(std::filesystem::file_size(filePath) / (1024 * 1024));
        }
        catch (...)
        {
            return -1;
        }
    }

    bool FileHelper::EnsurePathAndFileExists(const std::string &filePath)
    {
        try
        {
            std::filesystem::path path = filePath;
            if (path.has_extension())
            {
                path = path.parent_path();
            }
            std::filesystem::create_directories(path);

            if (!std::filesystem::exists(filePath))
            {
                std::ofstream(filePath).close();
            }

            return true;
        }
        catch (...)
        {
            return false;
        }
    }
}
