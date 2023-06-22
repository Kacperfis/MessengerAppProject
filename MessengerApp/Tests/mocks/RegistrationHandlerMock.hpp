#pragma once
#include <gmock/gmock.h>
#include <../MessengerInterfaces/IRegistrationHandler.hpp>

class RegistrationHandlerMock : public IRegistrationHandler
{
public:
    MOCK_METHOD(bool, registrationTrigger, (), (override));
    MOCK_METHOD((std::map<std::string, std::string>), getUsersData, (), (override));
    MOCK_METHOD(bool, isUserAlreadyRegistered, ((const std::map<std::string, std::string>&)), (override));
    MOCK_METHOD(void, saveUserDataForLoginAuthentication, (const std::string&, const std::string&), (override));
};
