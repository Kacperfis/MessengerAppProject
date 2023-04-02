#include <iostream>

#include "Helpers/UIHelper.hpp"

namespace helpers
{

void showEntryPage()
{
    std::cout << "================================================" << std::endl;
    std::cout << "==============Welcome in Messenger==============" << std::endl;
    std::cout << "1. Registration" << std::endl;
    std::cout << "2. Login(user)" << std::endl;
    std::cout << "3. Login (admin)" << std::endl;
}

void showRegistrationForm(
    std::string& login,
    std::string& password,
    std::istream& stdInput)
{
    std::cout << "================================================" << std::endl;
    std::cout << "type your login: " << std::endl;
    stdInput >> login;
    std::cout << "type your password: " << std::endl;
    stdInput >> password;
}

}  // namespace helpers