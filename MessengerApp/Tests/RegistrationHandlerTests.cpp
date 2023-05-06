#include <gtest/gtest.h>
#include <iostream>
#include <Tests/common/commonFixture.hpp>
#include <Registration/RegistrationHandler.hpp>
#include <Tests/mocks/DatabaseControllerMock.hpp>

using testing::Return;
using testing::_;

class RegistrationHandlerTests : public ::testing::Test
{
public:
    void SetUp()
    {
        const std::string input = "test_user\ntest_password\n";
        inputData_ = processInput(input);
        databaseControllerMock_ = std::make_shared<DatabaseControllerMock>();
        sut_ = std::make_shared<RegistrationHandler>(databaseControllerMock_, *inputData_.input);
    }

    void TearDown()
    {
        clearBuffer(inputData_.oldBuffer);
    }

    InputData inputData_;
    std::shared_ptr<DatabaseControllerMock> databaseControllerMock_;
    std::shared_ptr<RegistrationHandler> sut_;
};

TEST_F(RegistrationHandlerTests, shouldTriggerRegistrationAndRegisterUserSuccessfully)
{
    Logger::testName_ = "RegistrationHandlerTests_shouldTriggerRegistrationAndRegisterUserSuccessfully";
    std::map<std::string, std::string> registeredUsersData;
    registeredUsersData.insert(std::make_pair("test_user", "test_password"));

    EXPECT_CALL(*databaseControllerMock_, LoadDatabase())
        .Times(1);

    EXPECT_CALL(*databaseControllerMock_, getRegisteredUsersData())
        .WillOnce(Return(registeredUsersData));

    EXPECT_CALL(*databaseControllerMock_, registerUser(_,_))
        .Times(1);

    sut_->registrationTrigger();
}
