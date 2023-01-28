#pragma once

class ILoginHub
{
public: 
    virtual ~ILoginHub() {}
    virtual bool login();
    virtual bool logout();
};