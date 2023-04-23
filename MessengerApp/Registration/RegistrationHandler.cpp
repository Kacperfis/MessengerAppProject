#include <ranges>

#include "RegistrationHandler.hpp"
#include <Helpers/UIHelper.hpp>

RegistrationHandler::RegistrationHandler(const std::shared_ptr<IDatabaseController> databaseController, std::istream& inputStream)
    : databaseController_(databaseController), inputStream_(inputStream) {};

void RegistrationHandler::registrationTrigger()
{
    helpers::showRegistrationForm(login_, password_, inputStream_);
    registerUser();
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