#pragma once
#include <memory>
#include <ILoginHub.hpp>
#include <ILoginHubFactory.hpp>
#include <LoginHub/AdminLoginHubCreator.hpp>
#include <LoginHub/UserLoginHubCreator.hpp>
#include <LoginHub/AdminLoginHub.hpp>
#include <LoginHub/UserLoginHub.hpp>
#include <Registration/RegistrationHandler.hpp>
#include <Database/DatabaseController.hpp>

class MessengerAgent
{
public:
    MessengerAgent(const std::string& databasePath, std::istream& inputStream);
private:
    std::shared_ptr<UserLoginHub> userLoginHub_;
    std::shared_ptr<AdminLoginHub> AdminLoginHub_;
    std::shared_ptr<IRegistrationHandler> registrationHandler_;
    std::shared_ptr<DatabaseController> databaseController_;
    std::istream& inputStream_;
};
