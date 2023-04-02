#include <iostream>

#include "MessengerAgent.hpp"
#include <Helpers/UIHelper.hpp>

MessengerAgent::MessengerAgent(const std::string& databasePath, std::istream& inputStream) :
    userLoginHub_(std::make_shared<UserLoginHub>()),
    AdminLoginHub_(std::make_shared<AdminLoginHub>()),
    databaseController_(std::make_shared<DatabaseController>(databasePath)),
    inputStream_(inputStream)
{
    registrationHandler_ = std::make_shared<RegistrationHandler>(databaseController_, inputStream_);
    helpers::showEntryPage();
    int choice;
    inputStream_ >> choice;
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
