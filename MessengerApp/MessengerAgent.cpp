#include <iostream>

#include "MessengerAgent.hpp"
#include <Helpers/UIHelper.hpp>

MessengerAgent::MessengerAgent() :
    userLoginHub_(std::make_shared<UserLoginHub>()),
    AdminLoginHub_(std::make_shared<AdminLoginHub>()),
    registrationHandler_(std::make_shared<RegistrationHandler>())
{
    helpers::showEntryPage();
    int choice;
    std::cin >> choice;
    switch (choice)
    {
        case 1:
            registrationHandler_->registrationTrigger();
        break;
        case 2:
        //
        break;
        case 3:
        //
        break;
    }
}
