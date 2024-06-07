#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <Database/AdminDatabaseController.hpp>
#include <../MessengerInterfaces/IRegistrationHandler.hpp>

namespace registration
{

class AdminRegistrationHandler : public interface::IRegistrationHandler
{
public:
    AdminRegistrationHandler(const std::shared_ptr<interface::IDatabaseController>& adminDatabaseController, std::istream& inputStream);
    bool registrationTrigger() override;
    std::map<std::string, std::string> getData() override;
    bool isPersonAlreadyRegistered(const std::map<std::string, std::string>& data) override;
    void saveDataForLoginAuthentication(const std::string& login, const std::string& password) override;
private:
    bool registerAdmin();

    std::string login_;
    std::string password_;

    std::shared_ptr<interface::IDatabaseController> adminDatabaseController_;
    std::istream& inputStream_;
    Logger logger_;
};

} // namespace registration
