#include <gtest/gtest.h>
#include <iostream>

#include <Login/UserLoginHubCreator.hpp>
#include <Login/UserLoginHub.hpp>
#include <Tests/common/commonFixture.hpp>
#include <Tests/mocks/RegistrationHandlerMock.hpp>
#include <Common/Logger.hpp>

using testing::Return;
using testing::_;

TEST(UserLoginHubTests, shouldLoginAndLogoutSuccesfully)
{
    Logger::testName_ = "UserLoginHubTests_ShouldLoginAndLogoutSuccesfully";
    auto buffer = saveCleanOutputBuffer();

    auto registrationHandlerMock = std::make_shared<mocks::RegistrationHandlerMock>();
    auto LoginHubCreator = std::make_shared<login::UserLoginHubCreator>();
    auto LoginHub = LoginHubCreator->createHub();

    std::stringstream input("test_user\ntest_password\n");
    std::map<std::string, std::string> registeredUsersData;
    registeredUsersData.insert(std::make_pair("test_user", "test_password"));

    EXPECT_CALL(*registrationHandlerMock, getData())
        .WillOnce(Return(registeredUsersData));

    EXPECT_CALL(*registrationHandlerMock, saveDataForLoginAuthentication("test_user", "test_password"))
        .Times(1);

    EXPECT_CALL(*registrationHandlerMock, isPersonAlreadyRegistered(registeredUsersData))
        .WillOnce(Return(true));

    EXPECT_TRUE(LoginHub->login(input, registrationHandlerMock));
    EXPECT_TRUE(LoginHub->isLogged());
    EXPECT_TRUE(LoginHub->logout());
    EXPECT_FALSE(LoginHub->isLogged());

    clearBuffer(buffer);
}

TEST(UserLoginHubTests, shouldNotLoginDueToNotExistingUserDataInDatabase)
{
    Logger::testName_ = "UserLoginHubTests_ShouldNotLoginDueToNotExistingUserDataInDatabase";
    auto buffer = saveCleanOutputBuffer();

    auto registrationHandlerMock = std::make_shared<mocks::RegistrationHandlerMock>();
    auto LoginHubCreator = std::make_shared<login::UserLoginHubCreator>();
    auto LoginHub = LoginHubCreator->createHub();

    std::stringstream input("test_user2\ntest_password2\n");
    std::map<std::string, std::string> registeredUsersData;
    registeredUsersData.insert(std::make_pair("test_user", "test_password"));

    EXPECT_CALL(*registrationHandlerMock, getData())
        .WillOnce(Return(registeredUsersData));

    EXPECT_CALL(*registrationHandlerMock, saveDataForLoginAuthentication("test_user2", "test_password2"))
        .Times(1);

    EXPECT_CALL(*registrationHandlerMock, isPersonAlreadyRegistered(registeredUsersData))
        .WillOnce(Return(false));

    EXPECT_FALSE(LoginHub->login(input, registrationHandlerMock));
    EXPECT_FALSE(LoginHub->isLogged());

    clearBuffer(buffer);
}
