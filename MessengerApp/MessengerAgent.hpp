#pragma once
#include <memory>
#include <ILoginHub.hpp>
#include <ILoginHubFactory.hpp>
#include <Login/AdminLoginHubCreator.hpp>
#include <Login/UserLoginHubCreator.hpp>
#include <Login/AdminLoginHub.hpp>
#include <Login/UserLoginHub.hpp>
#include <Registration/RegistrationHandler.hpp>
#include <Database/DatabaseController.hpp>
#include <Connection/Server/Server.hpp>
#include <Connection/Client/Client.hpp>

namespace agent
{

class MessengerAgent
{
public:
    MessengerAgent(const std::string& databasePath, std::istream& inputStream);
private:
    std::shared_ptr<login::UserLoginHub> userLoginHub_;
    std::shared_ptr<login::AdminLoginHub> AdminLoginHub_;
    std::shared_ptr<interface::IRegistrationHandler> registrationHandler_;
    std::shared_ptr<database::DatabaseController> databaseController_;
    std::istream& inputStream_;

    std::shared_ptr<connection::server::Server> server_;
    std::shared_ptr<connection::client::Client> client_;
};

} // namespace agent
