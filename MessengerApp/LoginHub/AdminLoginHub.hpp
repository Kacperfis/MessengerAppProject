#pragma once

#include <memory>

#include <ILoginHub.hpp>
#include <LoginHub/LoginData.hpp>
#include <Common/Logger.hpp>
#include <../MessengerInterfaces/IRegistrationHandler.hpp>

class AdminLoginHub : public ILoginHub
{
public:
    AdminLoginHub();
    bool login(std::istream&, const std::shared_ptr<IRegistrationHandler>&) override;
    bool logout() override;
    bool setStatus(loginStatus) override;
    bool isLogged() override;
    const std::string getUserLogin() override;
private:
    bool adminLogged_;
    std::unique_ptr<LoginData> loginDataPtr_;
    Logger logger_;
};
