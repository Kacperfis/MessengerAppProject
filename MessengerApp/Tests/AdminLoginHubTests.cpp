#include <gtest/gtest.h>
#include <iostream>

#include <LoginHub/AdminLoginHubCreator.hpp>
#include <LoginHub/AdminLoginHub.hpp>
#include <Tests/common/commonFixture.hpp>

TEST(AdminLoginHubTests, ShouldLoginAndLogoutSuccesfully)
{
    auto LoginHubCreator = std::make_shared<AdminLoginHubCreator>();
    auto LoginHub = LoginHubCreator->createHub();

    const std::string input = "test_admin\ntest_password\n";
    auto inputData = processInput(input);
    EXPECT_TRUE(LoginHub->login(*inputData.input));
    EXPECT_TRUE(LoginHub->isLogged());
    EXPECT_TRUE(LoginHub->logout());
    EXPECT_FALSE(LoginHub->isLogged());

    clearBuffer(inputData.oldBuffer);
}
