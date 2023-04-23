#include <fstream>
#include <Tests/common/commonFixture.hpp>

TestInputStream::TestInputStream(const std::string& input) : std::istream(nullptr), input_(input)
{
    rdbuf(&inputBuf_);
}

NullStream::NullStream() : std::ostream(&someBuffer_) {}

int NullBuffer::overflow(int c) { return c; }

void clearFile(const std::string& path)
{
    std::ofstream file(path);
    file << "";
}

InputData processInput(const std::string& input)
{
    static TestInputStream testInput(input);
    static NullStream null_stream;
    std::streambuf* oldBuffer = std::cout.rdbuf();
    std::cout.rdbuf(null_stream.rdbuf());
    return {&testInput, oldBuffer};
}

void clearBuffer(std::streambuf* oldBuffer)
{
    std::cout.rdbuf(oldBuffer);
}
