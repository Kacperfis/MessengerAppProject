#include "UserLoginHub.hpp"
#include <Helpers/LoginHubHelper.hpp>

UserLoginHub::UserLoginHub() : logger_("UserLoginHub") {}

bool UserLoginHub::login(std::istream& stdInput)
{
    logger_.log(Severity::info, "Logging to the User account");
    loginDataPtr_ = std::move(helpers::login(stdInput));
    if (!setStatus(loginStatus::Logged))
    {
        logger_.log(Severity::warning, "Login unsuccessful");
        return false;
    }
    return true;
}

bool UserLoginHub::logout()
{
    if (!setStatus(loginStatus::LoggedOut))
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

bool UserLoginHub::setStatus(loginStatus status)
{
    switch (status)
    {
        case loginStatus::Logged:
            userLogged_ = true;
            break;
        case loginStatus::LoggedOut:
            userLogged_ = false;
            break;
    }
    return true;
}
