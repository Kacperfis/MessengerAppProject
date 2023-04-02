#include <gtest/gtest.h>
#include <iostream>

#include <LoginHub/UserLoginHubCreator.hpp>
#include <LoginHub/UserLoginHub.hpp>
#include <Tests/common/commonFixture.hpp>

TEST(UserLoginHubTests, ShouldLoginAndLogoutSuccesfully)
{
    auto LoginHubCreator = std::make_shared<UserLoginHubCreator>();
    auto LoginHub = LoginHubCreator->createHub();

    const std::string input = "test_user\ntest_password\n";
    auto inputData = processInput(input);
    EXPECT_TRUE(LoginHub->login(inputData.input));
    EXPECT_TRUE(LoginHub->isLogged());
    EXPECT_TRUE(LoginHub->logout());
    EXPECT_FALSE(LoginHub->isLogged());

    clearBuffer(inputData.oldBuffer);
}
