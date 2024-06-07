#include <ranges>
#include "AdminRegistrationHandler.hpp"
#include <Helpers/UIHelper.hpp>

namespace registration
{

AdminRegistrationHandler::AdminRegistrationHandler(
    const std::shared_ptr<interface::IDatabaseController>& adminDatabaseController,
    std::istream& inputStream) :
    adminDatabaseController_(adminDatabaseController),
    inputStream_(inputStream),
    logger_("AdminRegistrationHandler") {}

bool AdminRegistrationHandler::registrationTrigger()
{
    helpers::showRegistrationForm(login_, password_, inputStream_);
    return registerAdmin();
}

std::map<std::string, std::string> AdminRegistrationHandler::getData()
{
    adminDatabaseController_->loadDatabase();
    return adminDatabaseController_->getData();
}

bool AdminRegistrationHandler::registerAdmin()
{
    auto data = getData();
    if (!isPersonAlreadyRegistered(data))
    {
        adminDatabaseController_->registerPerson(login_, password_);
        logger_.log(Severity::info, "Admin registered succesfully");
        return true;
    }
    return false;
}

bool AdminRegistrationHandler::isPersonAlreadyRegistered(const std::map<std::string, std::string>& data)
{
    auto adminData = std::ranges::find_if(data,
    [this](const auto& item)
    {
        return item.first == login_;
    });

    if (adminData != data.end())
    {
        logger_.log(Severity::warning, "Admin with given login is already registered");
        return true;
    }

    return false;
}

void AdminRegistrationHandler::saveDataForLoginAuthentication(const std::string& login, const std::string& password)
{
    login_ = login;
    password_ = password;
}

} // namespace registration
