#pragma once

#include <Login/LoginData.hpp>
#include <IRegistrationHandler.hpp>

namespace interface
{

class ILoginHub
{
public: 
    virtual ~ILoginHub() {};
    virtual bool login(std::istream&, const std::shared_ptr<IRegistrationHandler>&) = 0;
    virtual bool logout() = 0;
    virtual bool setStatus(login::loginStatus) = 0;
    virtual bool isLogged() = 0;
    virtual const std::string getUserLogin() = 0;
};

} // namespace interface
