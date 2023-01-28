#include <iostream>

#include "AdminLoginHub.hpp"
#include <Helpers/LoginHubHelper.hpp>

bool AdminLoginHub::login(std::istream& stdInput)
{
   std::cout << "Logging admin" << std::endl;
    loginDataPtr_ = std::move(helpers::login(stdInput));
    if (!setStatus(loginStatus::Logged)) return false;
    return true;
}

bool AdminLoginHub::logout()
{
    if (!setStatus(loginStatus::LoggedOut)) return false;
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
