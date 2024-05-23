#include "UserLoginHub.hpp"
#include <Helpers/LoginHubHelper.hpp>
#include <Registration/RegistrationHandler.hpp>

namespace login
{

UserLoginHub::UserLoginHub() : logger_("UserLoginHub") {}

bool UserLoginHub::login(std::istream& stdInput, const std::shared_ptr<interface::IRegistrationHandler>& registrationHandler)
{
    logger_.log(Severity::info, "Logging to the User account");
    loginDataPtr_ = std::move(helpers::login(stdInput));
    auto registeredUsersData = registrationHandler->getUsersData();
    registrationHandler->saveUserDataForLoginAuthentication(loginDataPtr_->getLogin(), loginDataPtr_->getPassword());
    if (registrationHandler->isUserAlreadyRegistered(registeredUsersData))
    {
        if (helpers::checkUserCredentials(loginDataPtr_->getLogin(), loginDataPtr_->getPassword(), registeredUsersData))
        {
            if (!setStatus(login::loginStatus::Logged))
            {
                logger_.log(Severity::warning, "Login unsuccessful");
                return false;
            }
            logger_.log(Severity::info, "Login Successful");
            return true;
        }
    }
    return false;
}

bool UserLoginHub::logout()
{
    if (!setStatus(login::loginStatus::LoggedOut))
    {
        logger_.log(Severity::warning, "Logout unsuccessful");
        return false;
    }
    return true;
}

bool UserLoginHub::isLogged()
{
    return userLogged_;
}

bool UserLoginHub::setStatus(login::loginStatus status)
{
    switch (status)
    {
        case login::loginStatus::Logged:
            userLogged_ = true;
            break;
        case login::loginStatus::LoggedOut:
            userLogged_ = false;
            break;
    }
    return true;
}

const std::string UserLoginHub::getUserLogin()
{
    return loginDataPtr_->getLogin();
}

} // namespace login
