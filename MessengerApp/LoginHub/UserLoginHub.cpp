#include "UserLoginHub.hpp"
#include <Helpers/LoginHubHelper.hpp>

bool UserLoginHub::login(std::istream& stdInput)
{
    std::cout << "Logging user" << std::endl;
    loginDataPtr_ = std::move(helpers::login(stdInput));
    if (!setStatus(loginStatus::Logged)) return false;
    return true;
}

bool UserLoginHub::logout()
{
    if (!setStatus(loginStatus::LoggedOut)) return false;
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
