#pragma once

#include <ILoginHub.hpp>
#include <memory>

class AdminLoginHub : ILoginHub
{
public:
    bool login() override;
    bool logout() override;

private:

};