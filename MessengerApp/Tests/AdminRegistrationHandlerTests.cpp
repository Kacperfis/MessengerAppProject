#include <gtest/gtest.h>
#include <iostream>
#include <Tests/common/commonFixture.hpp>
#include <Registration/AdminRegistrationHandler.hpp>
#include <Tests/mocks/DatabaseControllerMock.hpp>

using testing::Return;
using testing::_;

TEST(AdminRegistrationHandlerTests, shouldTriggerRegistrationAndRegisterAdminSuccessfully)
{
    Logger::testName_ = "AdminRegistrationHandlerTests_shouldTriggerRegistrationAndRegisterUserSuccessfully";
    auto buffer = saveCleanOutputBuffer();

    std::stringstream input("test_admin2\ntest_password2\n");
    auto databaseControllerMock = std::make_shared<mocks::DatabaseControllerMock>();
    auto sut = std::make_shared<registration::AdminRegistrationHandler>(databaseControllerMock, input);
    std::map<std::string, std::string> registeredUsersData;
    registeredUsersData.insert(std::make_pair("test_admin", "test_password"));

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

TEST(AdminRegistrationHandlerTests, shouldTriggerRegistrationAndNotRegisterAlreadyRegisteredAdmin)
{
    Logger::testName_ = "AdminRegistrationHandlerTests_shouldTriggerRegistrationAndNotRegisterAlreadyRegisteredUser";
    auto buffer = saveCleanOutputBuffer();

    std::stringstream input("test_admin\ntest_password\n");
    auto databaseControllerMock = std::make_shared<mocks::DatabaseControllerMock>();
    auto sut = std::make_shared<registration::AdminRegistrationHandler>(databaseControllerMock, input);
    std::map<std::string, std::string> registeredUsersData;
    registeredUsersData.insert(std::make_pair("test_admin", "test_password"));

    EXPECT_CALL(*databaseControllerMock, loadDatabase())
        .Times(1);

    EXPECT_CALL(*databaseControllerMock, getData())
        .WillOnce(Return(registeredUsersData));

    auto result = sut->registrationTrigger();
    EXPECT_FALSE(result);

    clearBuffer(buffer);
}
