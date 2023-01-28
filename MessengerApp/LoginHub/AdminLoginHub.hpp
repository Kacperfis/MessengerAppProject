#pragma once

#include <memory>

#include <ILoginHub.hpp>
#include <LoginHub/LoginData.hpp>

class AdminLoginHub : public ILoginHub
{
public:
    bool login(std::istream& stdInput) override;
    bool logout() override;
    bool setStatus(loginStatus) override;
    bool isLogged() override;
private:
    bool adminLogged_;
    std::unique_ptr<LoginData> loginDataPtr_;
};
