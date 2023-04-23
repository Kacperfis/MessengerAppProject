#pragma once
#include <gmock/gmock.h>
#include <../MessengerInterfaces/IDatabaseController.hpp>

class DatabaseControllerMock : public IDatabaseController
{
public:
    MOCK_METHOD(void, LoadDatabase, (), (override));
    MOCK_METHOD(void, registerUser, (const std::string&, const std::string&), (override));
    MOCK_METHOD((const std::map<std::string, std::string>), getRegisteredUsersData, (), (const override));
};
