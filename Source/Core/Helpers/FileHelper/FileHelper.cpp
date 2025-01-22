#include "FileHelper.h"
#include <filesystem>
#include <sstream>
#include <fstream>

namespace Core::Helpers
{
    std::string FileHelper::ReadFile(const std::string &filePath)
    {
        EnsurePathAndFileExists(filePath);

        std::stringstream content;
        std::ifstream file(filePath);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        content << file.rdbuf();
        return content.str();
    }

    void FileHelper::AppendToFile(const std::string &filePath, const std::string &content)
    {
        EnsurePathAndFileExists(filePath);

        std::ofstream file(filePath, std::ios::app);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        file << content << std::endl;
    }

    void FileHelper::WriteToFile(const std::string &filePath, const std::string &content)
    {
        std::ofstream file(filePath);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        file << content;
    }

    int FileHelper::GetFileSizeInMB(const std::string &filePath)
    {
        EnsurePathAndFileExists(filePath);

        auto fileSizeBytes = std::filesystem::file_size(filePath);
        return static_cast<int>(fileSizeBytes / (1024 * 1024));
    }

    void FileHelper::EnsurePathAndFileExists(const std::string &filePath)
    {
        std::filesystem::path path = filePath;

        if (path.has_extension())
        {
            path = path.parent_path();
        }

        if (!std::filesystem::exists(path))
        {
            if (!std::filesystem::create_directories(path))
            {
                throw std::runtime_error("Failed to create directory: " + path.string());
            }
        }

        if (!std::filesystem::exists(filePath))
        {
            std::ofstream(filePath).close();
            if (!std::filesystem::exists(filePath))
            {
                throw std::runtime_error("Failed to create file: " + filePath);
            }
        }
    }
}
