#pragma once

#include <ILoginHub.hpp>
#include <memory>

class UserLoginHub : public ILoginHub
{
public:
    bool login() override;
    bool logout() override;

private:

};