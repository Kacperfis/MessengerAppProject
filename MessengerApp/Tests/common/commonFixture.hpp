#pragma once
#include <string>
#include <iostream>
#include <sstream>

class TestInputStream : public std::istream
{
public:
    TestInputStream(const std::string& input);
protected:
    std::stringbuf inputBuf_;
    std::string input_;
};

class NullBuffer : public std::streambuf
{
public:
    int overflow(int c);
};

class NullStream : public std::ostream
{
public:
    NullStream();
private:
    NullBuffer someBuffer_;
};

struct InputData
{
    TestInputStream* input;
    std::streambuf* oldBuffer;
};

void clearFile(const std::string& path);
InputData processInput(const std::string& input);
void clearBuffer(std::streambuf* oldBuffer);
