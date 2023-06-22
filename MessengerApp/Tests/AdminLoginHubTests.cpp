#include <gtest/gtest.h>
#include <iostream>

#include <LoginHub/AdminLoginHubCreator.hpp>
#include <LoginHub/AdminLoginHub.hpp>
#include <Tests/common/commonFixture.hpp>
#include <Common/Logger.hpp>

// TEST(AdminLoginHubTests, ShouldLoginAndLogoutSuccesfully)
// {
//     Logger::testName_ = "AdminLoginHubTests_ShouldLoginAndLogoutSuccesfully";
//     auto buffer = saveCleanOutputBuffer();

//     auto LoginHubCreator = std::make_shared<AdminLoginHubCreator>();
//     auto LoginHub = LoginHubCreator->createHub();

//     std::stringstream input("test_admin\ntest_password\n");
//     EXPECT_TRUE(LoginHub->login(input));
//     EXPECT_TRUE(LoginHub->isLogged());
//     EXPECT_TRUE(LoginHub->logout());
//     EXPECT_FALSE(LoginHub->isLogged());

//     clearBuffer(buffer);
// }
