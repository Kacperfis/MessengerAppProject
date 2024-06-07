#pragma once

namespace helpers
{

void showEntryPage();
void showRegistrationForm(std::string& login, std::string& password, std::istream& stdInput);

void showRegistrationOptionPage();
void showLoginOptionPage();

void showServerOrClientChoiceFormForUser();
void showServerOrClientChoiceFormForAdmin();

void userAlreadyRegisteredMessage();
void adminAlreadyRegisteredMessage();
void userSuccessfullyRegisteredMessage();

}  // namespace helpers
