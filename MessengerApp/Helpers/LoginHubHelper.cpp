#include <iostream>

#include "LoginHubHelper.hpp"

namespace helpers
{

std::unique_ptr<LoginData> login(std::istream& stdInput)
{
    std::cout << "login: ";
    std::string login, password;
    stdInput >> login;
    std::cout << std::endl << "password: ";
    stdInput >> password;
    std::cout << std::endl;

    return std::make_unique<LoginData>(login, password);
}

}  // namespace helpers
