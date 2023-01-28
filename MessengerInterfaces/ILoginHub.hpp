#pragma once

#include <LoginHub/LoginData.hpp>

class ILoginHub
{
public: 
    virtual ~ILoginHub() {};
    virtual bool login(std::istream&) = 0;
    virtual bool logout() = 0;
    virtual bool setStatus(loginStatus) = 0;
    virtual bool isLogged() = 0;
};
