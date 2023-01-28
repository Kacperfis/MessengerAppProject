#include <iostream>

#include "MessengerAgent.hpp"
#include <LoginHub/AdminLoginHubCreator.hpp>

MessengerAgent::MessengerAgent()
{
    auto adminLoginHubCreator = std::make_shared<AdminLoginHubCreator>();
    adminLoginHub_ = adminLoginHubCreator->createHub();

    auto x = adminLoginHub_->login();
    auto y = adminLoginHub_->logout();
    
    std::cout << "x: " << x << ", y:  " << y << std::endl;
}