#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <Database/DatabaseController.hpp>


class RegistrationHandler
{
public:
    RegistrationHandler(const std::shared_ptr<DatabaseController> databaseController, std::istream& inputStream);
    void registrationTrigger();
    void registerUser();
private:
    std::string login_;
    std::string password_;
    std::shared_ptr<DatabaseController> databaseController_;
    std::istream& inputStream_;
};

