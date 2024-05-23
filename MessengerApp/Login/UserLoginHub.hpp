#pragma once
#include <memory>
#include <iostream>

#include <ILoginHub.hpp>
#include <Login/LoginData.hpp>
#include <Common/Logger.hpp>
#include <../MessengerInterfaces/IRegistrationHandler.hpp>

namespace login
{

class UserLoginHub : public interface::ILoginHub
{
public:
    UserLoginHub();
    bool login(std::istream& stdInput, const std::shared_ptr<interface::IRegistrationHandler>& registrationHandler) override;
    bool logout() override;
    bool setStatus(login::loginStatus) override;
    bool isLogged() override;
    const std::string getUserLogin() override;
private:
    bool userLogged_;
    std::unique_ptr<login::LoginData> loginDataPtr_;
    Logger logger_;
};

} // namespace login
