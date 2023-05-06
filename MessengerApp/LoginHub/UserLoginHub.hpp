#pragma once
#include <memory>
#include <iostream>

#include <ILoginHub.hpp>
#include <LoginHub/LoginData.hpp>
#include <Common/Logger.hpp>

class UserLoginHub : public ILoginHub
{
public:
    UserLoginHub();
    bool login(std::istream& stdInput) override;
    bool logout() override;
    bool setStatus(loginStatus) override;
    bool isLogged() override;
private:
    bool userLogged_;
    std::unique_ptr<LoginData> loginDataPtr_;
    Logger logger_;
};
