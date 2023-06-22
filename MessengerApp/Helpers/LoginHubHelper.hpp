#pragma once
#include <memory>

#include <LoginHub/LoginData.hpp>

namespace helpers
{

std::unique_ptr<LoginData> login(std::istream& stdInput);
bool checkUserCredentials(const std::string& login, const std::string& password, const std::map<std::string, std::string>& registeredUsersData);

}  // namespace helpers