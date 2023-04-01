#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <Database/DatabaseController.hpp>

enum class accountType
{
    User,
    Admin
};

class RegistrationHandler
{
public:
    RegistrationHandler(){};
    void registrationTrigger();
    void registerAdmin();
    void registerUser();
private:
    std::string login_;
    std::string password_;
    accountType accountType_;
    std::shared_ptr<DatabaseController> databaseController_;
};

