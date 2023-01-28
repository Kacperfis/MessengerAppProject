#include <gtest/gtest.h>
#include <iostream>

#include <LoginHub/UserLoginHubCreator.hpp>
#include <LoginHub/UserLoginHub.hpp>

class TestInputStream : public std::istream
{
public:
    TestInputStream(const std::string& input) : std::istream(nullptr), input_(input)
    {
        rdbuf(&inputBuf_);
    }
protected:
    std::stringbuf inputBuf_;
    std::string input_;
};

class NullBuffer : public std::streambuf
{
public:
    int overflow(int c) { return c; }
};

class NullStream : public std::ostream
{
public:
    NullStream() : std::ostream(&someBuffer) {}
private:
    NullBuffer someBuffer;
};

TEST(UserLoginHubTests, ShouldLoginAndLogoutSuccesfully)
{
    auto LoginHubCreator = std::make_shared<UserLoginHubCreator>();
    auto LoginHub = LoginHubCreator->createHub();

    const std::string input = "test_user\ntest_password\n";
    TestInputStream testInput(input);
    NullStream null_stream;
    std::streambuf* oldBuffer = std::cout.rdbuf();
    std::cout.rdbuf(null_stream.rdbuf());

    EXPECT_TRUE(LoginHub->login(testInput));
    EXPECT_TRUE(LoginHub->isLogged());
    EXPECT_TRUE(LoginHub->logout());
    EXPECT_FALSE(LoginHub->isLogged());

    std::cout.rdbuf(oldBuffer);
}
