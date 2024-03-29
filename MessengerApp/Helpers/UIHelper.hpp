#pragma once

#include <Registration/RegistrationHandler.hpp>

namespace helpers
{

void showEntryPage();
void showRegistrationForm(std::string& login, std::string& password, std::istream& stdInput);
void showServerOrClientChoiceForm();
void userAlreadyRegisteredMessage();
void userSuccessfullyRegisteredMessage();

}  // namespace helpers
