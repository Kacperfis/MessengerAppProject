#include <gtest/gtest.h>
#include <iostream>
#include <Tests/common/commonFixture.hpp>
#include <Registration/UserRegistrationHandler.hpp>
#include <Tests/mocks/DatabaseControllerMock.hpp>

using testing::Return;
using testing::_;

TEST(UserRegistrationHandlerTests, shouldTriggerRegistrationAndRegisterUserSuccessfully)
{
    Logger::testName_ = "UserRegistrationHandlerTests_shouldTriggerRegistrationAndRegisterUserSuccessfully";
    auto buffer = saveCleanOutputBuffer();

    std::stringstream input("test_user2\ntest_password2\n");
    auto databaseControllerMock = std::make_shared<mocks::DatabaseControllerMock>();
    auto sut = std::make_shared<registration::UserRegistrationHandler>(databaseControllerMock, input);
    std::map<std::string, std::string> registeredUsersData;
    registeredUsersData.insert(std::make_pair("test_user", "test_password"));

    EXPECT_CALL(*databaseControllerMock, loadDatabase())
        .Times(1);

    EXPECT_CALL(*databaseControllerMock, getData())
        .WillOnce(Return(registeredUsersData));

    EXPECT_CALL(*databaseControllerMock, registerPerson(_,_))
        .Times(1);

    auto result = sut->registrationTrigger();
    EXPECT_TRUE(result);

    clearBuffer(buffer);
}

TEST(UserRegistrationHandlerTests, shouldTriggerRegistrationAndNotRegisterAlreadyRegisteredUser)
{
    Logger::testName_ = "UserRegistrationHandlerTests_shouldTriggerRegistrationAndNotRegisterAlreadyRegisteredUser";
    auto buffer = saveCleanOutputBuffer();

    std::stringstream input("test_user\ntest_password\n");
    auto databaseControllerMock = std::make_shared<mocks::DatabaseControllerMock>();
    auto sut = std::make_shared<registration::UserRegistrationHandler>(databaseControllerMock, input);
    std::map<std::string, std::string> registeredUsersData;
    registeredUsersData.insert(std::make_pair("test_user", "test_password"));

    EXPECT_CALL(*databaseControllerMock, loadDatabase())
        .Times(1);

    EXPECT_CALL(*databaseControllerMock, getData())
        .WillOnce(Return(registeredUsersData));

    auto result = sut->registrationTrigger();
    EXPECT_FALSE(result);

    clearBuffer(buffer);
}
