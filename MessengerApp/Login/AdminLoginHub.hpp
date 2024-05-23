#pragma once

#include <memory>

#include <ILoginHub.hpp>
#include <Login/LoginData.hpp>
#include <Common/Logger.hpp>
#include <../MessengerInterfaces/IRegistrationHandler.hpp>

namespace login
{

class AdminLoginHub : public interface::ILoginHub
{
public:
    AdminLoginHub();
    bool login(std::istream&, const std::shared_ptr<interface::IRegistrationHandler>&) override;
    bool logout() override;
    bool setStatus(login::loginStatus) override;
    bool isLogged() override;
    const std::string getUserLogin() override;
private:
    bool adminLogged_;
    std::unique_ptr<login::LoginData> loginDataPtr_;
    Logger logger_;
};

} // namespace login
