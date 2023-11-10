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
                std::cout << "enter your login and password" << std::endl;
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
                            client_ = std::make_shared<Client>();
                            client_->connect("127.0.0.1", "8080");
                            std::thread ioThread([this] { client_->run(); }); // Run io_context in a separate thread

                            std::string username;
                            std::cout << "Enter your username: ";
                            std::cin >> username;
                            client_->login(username);
                            std::string recipient, message;
                            std::cout << std::endl;
                            std::cout << "Enter recipient (or 'exit' to logout): ";
                            std::cin >> recipient;
                            while (true)
                            {
                                std::cout << "Enter your message: ";

                                std::cin.ignore();
                                std::getline(std::cin, message);
                                client_->sendMessage(username, recipient, message);
                            }

                            ioThread.join(); // Wait for the io_context thread to finish
                        }
                        case 2: //server
                        {
                            server_ = std::make_shared<Server>();
                            server_->start();
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
