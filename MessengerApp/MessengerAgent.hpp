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
#include <Connection/Server/Server.hpp>
#include <Connection/Client/Client.hpp>

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

    std::shared_ptr<Server> server_;
    std::shared_ptr<Client> client_;
};
