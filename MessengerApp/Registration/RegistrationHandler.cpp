#include <ranges>

#include "RegistrationHandler.hpp"
#include <Helpers/UIHelper.hpp>

void RegistrationHandler::registrationTrigger()
{
    helpers::showRegistrationForm(login_, password_, accountType_, std::cin);
    if (accountType_ == accountType::User)
    {
        registerUser();
    }
    else if (accountType_ == accountType::Admin)
    {
        registerAdmin();
    }
}

void RegistrationHandler::registerAdmin()
{
    return;
}

void RegistrationHandler::registerUser()
{
    databaseController_->LoadDatabase();
    auto registeredUsersData = databaseController_->getRegisteredUsersData();
    auto userData = std::ranges::find_if(registeredUsersData, [this](const auto& item){
        return item.first == login_ && item.second == password_;
    });
    if (userData != registeredUsersData.end())
    {
        std::cout << "User with given login is already registered" << std::endl;
        return;
    }
    databaseController_->registerUser(login_, password_);
}