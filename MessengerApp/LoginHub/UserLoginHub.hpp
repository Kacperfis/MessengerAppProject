#pragma once
#include <memory>
#include <iostream>

#include <ILoginHub.hpp>
#include <LoginHub/LoginData.hpp>

class UserLoginHub : public ILoginHub
{
public:
    bool login(std::istream& stdInput) override;
    bool logout() override;
    bool setStatus(loginStatus) override;
    bool isLogged() override;
private:
    bool userLogged_;
    std::unique_ptr<LoginData> loginDataPtr_;
};
