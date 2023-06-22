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
        {
            auto registrationResult = registrationHandler_->registrationTrigger();
            if (registrationResult) helpers::userSuccessfullyRegisteredMessage();
            else helpers::userAlreadyRegisteredMessage();
            break;
        }
        case 2:
        {
            auto loginResult = userLoginHub_->login(inputStream_, registrationHandler_);
            if (loginResult)
            {
                ///
            }
            break;
        }
    }
}
