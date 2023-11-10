#include <iostream>

#include "Helpers/UIHelper.hpp"
#include <Common/Logger.hpp>

namespace helpers
{

void showEntryPage()
{
    std::cout << "================================================" << std::endl;
    std::cout << "==============Welcome in Messenger==============" << std::endl;
    std::cout << "1. Registration" << std::endl;
    std::cout << "2. Login(user)" << std::endl;
    std::cout << "3. Exit" << std::endl;
}
void showRegistrationForm(std::string& login, std::string& password, std::istream& stdInput)
{
    std::cout << "================================================" << std::endl;
    std::cout << "type your login: " << std::endl;
    stdInput >> login;
    std::cout << "type your password: " << std::endl;
    stdInput >> password;
}

void showServerOrClientChoiceForm()
{
    std::cout << "choose the option: " << std::endl;
    std::cout << "1. Client" << std::endl;
    std::cout << "2. Server" << std::endl;
}

void userAlreadyRegisteredMessage()
{
    std::cout << "User with given login is already registered" << std::endl;
}

void userSuccessfullyRegisteredMessage()
{
    std::cout << "your account has ben registered successfully" << std::endl;
}

}  // namespace helpers