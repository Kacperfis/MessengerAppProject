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

    bool retryToMainWindow = true;
    while (retryToMainWindow)
    {
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
                    std::cout << "successfully logged in" << std::endl;
                    retryToMainWindow = false;

                    helpers::showServerOrClientChoiceForm();
                    int serviceChoice;
                    inputStream_ >> serviceChoice;
                    switch (serviceChoice)
                    {
                        case 1: //client
                        {
                            break;
                        }
                        case 2: //server
                        {
                            break;
                        }
                        default:
                        {
                            std::cerr << "Invalid choice, please try again" << std::endl;
                            break;
                        }
                    }
                }
                else std::cout << "logging failed!" << std::endl;
                break;
            }
            case 3:
            {
                std::cout << "Exiting application..." << std::endl;
                retryToMainWindow = false;
                break;
            }
            default:
            {
                std::cerr << "Invalid choice, please try again" << std::endl;
                break;
            }
        }
    }
}
