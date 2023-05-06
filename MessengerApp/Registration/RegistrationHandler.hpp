#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <Database/DatabaseController.hpp>


class RegistrationHandler
{
public:
    RegistrationHandler(const std::shared_ptr<IDatabaseController> databaseController, std::istream& inputStream);
    void registrationTrigger();
private:
    void registerUser();
    std::string login_;
    std::string password_;
    std::shared_ptr<IDatabaseController> databaseController_;
    std::istream& inputStream_;
    Logger logger_;
};

