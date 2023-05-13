#include <ranges>
#include "RegistrationHandler.hpp"
#include <Helpers/UIHelper.hpp>

RegistrationHandler::RegistrationHandler(const std::shared_ptr<IDatabaseController> databaseController, std::istream& inputStream)
    : databaseController_(databaseController), inputStream_(inputStream), logger_("RegistrationHandler") {};

bool RegistrationHandler::registrationTrigger()
{
    helpers::showRegistrationForm(login_, password_, inputStream_);
    return registerUser();
}

bool RegistrationHandler::registerUser()
{
    databaseController_->LoadDatabase();
    auto registeredUsersData = databaseController_->getRegisteredUsersData();
    if (!isUserAlreadyRegistered(registeredUsersData))
    {
        databaseController_->registerUser(login_, password_);
        logger_.log(Severity::info, "Registration succesfull");
        return true;
    }
    return false;
}

bool RegistrationHandler::isUserAlreadyRegistered(const std::map<std::string, std::string>& registeredUsersData)
{
    auto userData = std::ranges::find_if(registeredUsersData, [this](const auto& item){
        return item.first == login_;
    });
    if (userData != registeredUsersData.end())
    {
        logger_.log(Severity::warning, "User with given login is already registered");
        return true;
    }
    return false;
}