#pragma once

#include <ILoginHub.hpp>
#include <memory>

class UserLoginHub : ILoginHub
{
public:
    bool login() override;
    bool logout() override;

private:

};