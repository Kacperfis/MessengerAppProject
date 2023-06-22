#pragma once

#include <map>
#include <string>

class IRegistrationHandler
{
public:
    virtual ~IRegistrationHandler() {};
    virtual bool registrationTrigger() = 0;
    virtual std::map<std::string, std::string> getUsersData() = 0;
    virtual bool isUserAlreadyRegistered(const std::map<std::string, std::string>&) = 0;
    virtual void saveUserDataForLoginAuthentication(const std::string&, const std::string&) = 0;
};
