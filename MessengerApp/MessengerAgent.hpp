#pragma once
#include <memory>
#include <ILoginHub.hpp>
#include <ILoginHubFactory.hpp>
#include <Login/AdminLoginHubCreator.hpp>
#include <Login/UserLoginHubCreator.hpp>
#include <Login/AdminLoginHub.hpp>
#include <Login/UserLoginHub.hpp>
#include <Registration/UserRegistrationHandler.hpp>
#include <Registration/AdminRegistrationHandler.hpp>
#include <Database/UserDatabaseController.hpp>
#include <Database/AdminDatabaseController.hpp>
#include <Connection/Server/Server.hpp>
#include <Connection/Client/Client.hpp>

namespace agent
{

enum class AccountType
{
    User,
    Admin
};

class MessengerAgent
{
public:
    MessengerAgent(const std::string& usersDatabasePath, const std::string& adminDatabasePath, std::istream& inputStream);
private:

    void handleRegistration();
    std::pair<bool, AccountType> handleLogin();

    bool startClient(const std::string& username);
    void startServer();

    std::istream& inputStream_;
    std::shared_ptr<interface::ILoginHub> userLoginHub_;
    std::shared_ptr<interface::ILoginHub> adminLoginHub_;

    std::shared_ptr<interface::IDatabaseController> userDatabaseController_;
    std::shared_ptr<interface::IDatabaseController> adminDatabaseController_;

    std::shared_ptr<interface::IRegistrationHandler> userRegistrationHandler_;
    std::shared_ptr<interface::IRegistrationHandler> adminRegistrationHandler_;

    std::shared_ptr<connection::server::Server> server_;
    std::shared_ptr<connection::client::Client> client_;
};

} // namespace agent
