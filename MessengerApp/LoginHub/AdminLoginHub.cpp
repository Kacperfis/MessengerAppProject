#include <iostream>

#include "AdminLoginHub.hpp"
#include <Helpers/LoginHubHelper.hpp>

AdminLoginHub::AdminLoginHub() : logger_("AdminLoginHub") {}

bool AdminLoginHub::login(std::istream& stdInput, const std::shared_ptr<IRegistrationHandler>& registrationHandlerPtr)
{
    logger_.log(Severity::info, "Logging to the Admin account");
    loginDataPtr_ = std::move(helpers::login(stdInput));
    if (!setStatus(loginStatus::Logged))
    {
        logger_.log(Severity::warning, "Login unsuccessful");
        return false;
    }
    return true;
}

bool AdminLoginHub::logout()
{
    if (!setStatus(loginStatus::LoggedOut))
    {
        logger_.log(Severity::warning, "Logout unsuccessful");
        return false;
    }
    return true;
}

bool AdminLoginHub::isLogged()
{
    return adminLogged_;
}

bool AdminLoginHub::setStatus(loginStatus status)
{
    switch (status)
    {
        case loginStatus::Logged:
            adminLogged_ = true;
            break;
        case loginStatus::LoggedOut:
            adminLogged_ = false;
            break;
    }
    return true;
}
