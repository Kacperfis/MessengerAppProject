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
    return;
}