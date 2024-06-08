#include <iostream>

#include "MessengerAgent.hpp"
#include <Helpers/UIHelper.hpp>

namespace agent
{

MessengerAgent::MessengerAgent(const std::string& usersDatabasePath, const std::string& adminDatabasePath, std::istream& inputStream) :
    inputStream_(inputStream),
    userLoginHub_(std::make_shared<login::UserLoginHub>()),
    adminLoginHub_(std::make_shared<login::AdminLoginHub>()),
    userDatabaseController_(std::make_shared<database::UserDatabaseController>(usersDatabasePath)),
    adminDatabaseController_(std::make_shared<database::AdminDatabaseController>(adminDatabasePath)),
    userRegistrationHandler_(std::make_shared<registration::UserRegistrationHandler>(userDatabaseController_, inputStream)),
    adminRegistrationHandler_(std::make_shared<registration::AdminRegistrationHandler>(adminDatabaseController_, inputStream))
{
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
                handleRegistration();
                break;
            }
            case 2:
            {
                auto loginResult = handleLogin();
                if (loginResult.first)
                {
                    std::cout << "successfully logged in" << std::endl;
                    retryToMainWindow = false;

                    if (loginResult.second == AccountType::User)
                    {
                        helpers::showServerOrClientChoiceFormForUser();
                    }
                    else
                    {
                        helpers::showServerOrClientChoiceFormForAdmin();
                    }

                    int serviceChoice;
                    inputStream_ >> serviceChoice;
                    switch (serviceChoice)
                    {
                        case 1: // client
                        {
                            while (true)
                            {
                                std::string username;
                                loginResult.second == AccountType::User ? username = userLoginHub_->getUserLogin() : username = adminLoginHub_->getUserLogin();
                                auto result = startClient(username);
                                if (result) break;
                            }
                        }
                        case 2: // server
                        {
                            startServer();
                        }
                        default:
                        {
                            std::cerr << "Invalid choice, please try again" << std::endl;
                            break;
                        }
                    }
                    break;
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

void MessengerAgent::handleRegistration()
{
    helpers::showRegistrationOptionPage();
    int accountType;
    inputStream_ >> accountType;

    switch (accountType)
    {
        case 1:
        {
            auto registrationResult = userRegistrationHandler_->registrationTrigger();
            if (registrationResult) helpers::userSuccessfullyRegisteredMessage();
            else helpers::userAlreadyRegisteredMessage();
            break;
        }
        case 2:
        {
            auto registrationResult = adminRegistrationHandler_->registrationTrigger();
            if (registrationResult) helpers::userSuccessfullyRegisteredMessage();
            else helpers::adminAlreadyRegisteredMessage();
            break;
        }
        default:
        {
            std::cerr << "Invalid choice, please try again" << std::endl;
            break;
        }
    }
}

std::pair<bool, AccountType> MessengerAgent::handleLogin()
{
    helpers::showLoginOptionPage();
    int accountType;
    inputStream_ >> accountType;
    std::cout << "enter your login and password" << std::endl;
    switch (accountType)
    {
        case 1:
        {
            return std::make_pair(userLoginHub_->login(inputStream_, userRegistrationHandler_), AccountType::User);
            break;
        }
        case 2:
        {
            return std::make_pair(adminLoginHub_->login(inputStream_, adminRegistrationHandler_), AccountType::Admin);
            break;
        }
        default:
        {
            std::cerr << "Invalid choice, please try again" << std::endl;
            break;
        }
    }

    return {};
}

bool MessengerAgent::startClient(const std::string& username)
{
    client_ = std::make_shared<connection::client::Client>();
    client_->connect("127.0.0.1", "8080");
    std::thread ioThread([this] { client_->run(); }); // run io_context in a separate thread

    client_->login(username);
    std::string recipient, message;
    std::cout << std::endl;
    std::cout << "Enter recipient (or 'EXIT'): " << std::endl;
    std::cin >> recipient;
    std::cin.ignore();
    if (recipient == "EXIT")
    {
        ioThread.join();
        client_->stop();
        return true;
    }
    while (true)
    {
        std::cout << "Enter your message (or 'EXIT'): " << std::endl;
        std::getline(std::cin, message);
        if (message == "EXIT")
        {
            break;
        }
        client_->sendMessage(username, recipient, message);
    }

    ioThread.join(); // wait for the io_context thread to finish
    client_->stop();
    return true;
}

void MessengerAgent::startServer()
{
    server_ = std::make_shared<connection::server::Server>();
    server_->start();
}

} // namespace agent
