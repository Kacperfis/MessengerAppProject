#pragma once

#include <Registration/RegistrationHandler.hpp>

namespace helpers
{

void showEntryPage();
void showRegistrationForm(
    std::string& login,
    std::string& password,
    accountType& type,
    std::istream& stdInput);

}  // namespace helpers
