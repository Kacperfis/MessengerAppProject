#pragma once

#include <LoginHub/LoginData.hpp>
#include <Registration/RegistrationHandler.hpp>
#include <IRegistrationHandler.hpp>

class ILoginHub
{
public: 
    virtual ~ILoginHub() {};
    virtual bool login(std::istream&, const std::shared_ptr<IRegistrationHandler>&) = 0;
    virtual bool logout() = 0;
    virtual bool setStatus(loginStatus) = 0;
    virtual bool isLogged() = 0;
    virtual const std::string getUserLogin() = 0;
};
