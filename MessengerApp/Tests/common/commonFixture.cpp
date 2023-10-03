#include <fstream>
#include <filesystem>
#include <Tests/common/commonFixture.hpp>

NullStream::NullStream() : std::ostream(&someBuffer_) {}

void clearFile(const std::string& path)
{
    std::ofstream file(path);
    file << "";
}

void clearAllFilesFromFolder(const std::string& folderPath)
{
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath))
        {
            if (std::filesystem::is_regular_file(entry))
            {
                const std::string fileName = entry.path().filename().string();
                if (fileName.find("data" == 0) && fileName.find("dataIndex") != 0)
                {
                    std::filesystem::remove(entry.path());
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return;
    }
}

void setDefaultValueForIndexFile(const std::string& filePath, const std::string& value)
{
    std::ofstream indexFile(filePath + "dataIndex.txt", std::ios::trunc);

    if (indexFile.is_open())
    {
        indexFile << value;
        indexFile.close();
    }
    else std::cerr << "Error opening index file to update to default value";
}

std::streambuf* saveCleanOutputBuffer()
{
    static NullStream null_stream;
    std::streambuf* buffer = std::cout.rdbuf();
    std::cout.rdbuf(null_stream.rdbuf());
    return buffer;
}

void clearBuffer(std::streambuf* oldBuffer)
{
    std::cout.rdbuf(oldBuffer);
}
