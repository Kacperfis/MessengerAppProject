#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <Database/DatabaseController.hpp>
#include <../MessengerInterfaces/IRegistrationHandler.hpp>

class RegistrationHandler : public IRegistrationHandler
{
public:
    RegistrationHandler(const std::shared_ptr<IDatabaseController> databaseController, std::istream& inputStream);
    bool registrationTrigger() override;
    std::map<std::string, std::string> getUsersData() override;
    bool isUserAlreadyRegistered(const std::map<std::string, std::string>& registeredUsersData) override;
    void saveUserDataForLoginAuthentication(const std::string& login, const std::string& password) override;
private:
    bool registerUser();
    std::string login_;
    std::string password_;
    std::shared_ptr<IDatabaseController> databaseController_;
    std::istream& inputStream_;
    Logger logger_;
};

