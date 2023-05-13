#include <gtest/gtest.h>
#include <iostream>

#include <LoginHub/UserLoginHubCreator.hpp>
#include <LoginHub/UserLoginHub.hpp>
#include <Tests/common/commonFixture.hpp>
#include <Common/Logger.hpp>

TEST(UserLoginHubTests, ShouldLoginAndLogoutSuccesfully)
{
    Logger::testName_ = "UserLoginHubTests_ShouldLoginAndLogoutSuccesfully";
    auto buffer = saveCleanOutputBuffer();

    auto LoginHubCreator = std::make_shared<UserLoginHubCreator>();
    auto LoginHub = LoginHubCreator->createHub();

    std::stringstream input("test_user\ntest_password\n");
    EXPECT_TRUE(LoginHub->login(input));
    EXPECT_TRUE(LoginHub->isLogged());
    EXPECT_TRUE(LoginHub->logout());
    EXPECT_FALSE(LoginHub->isLogged());

    clearBuffer(buffer);
}
