#include <fstream>
#include <Tests/common/commonFixture.hpp>

NullStream::NullStream() : std::ostream(&someBuffer_) {}

void clearFile(const std::string& path)
{
    std::ofstream file(path);
    file << "";
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
