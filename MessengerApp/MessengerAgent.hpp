#pragma once
#include <memory>
#include <ILoginHub.hpp>
#include <ILoginHubFactory.hpp>
#include <LoginHub/AdminLoginHub.hpp>
#include <LoginHub/UserLoginHub.hpp>
#include <Registration/RegistrationHandler.hpp>

class MessengerAgent
{
public:
    MessengerAgent();
private:
    std::shared_ptr<UserLoginHub> userLoginHub_;
    std::shared_ptr<AdminLoginHub> AdminLoginHub_;
    std::shared_ptr<RegistrationHandler> registrationHandler_;
    
};
