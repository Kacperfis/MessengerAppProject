#pragma once
#include <memory>
#include <ILoginHub.hpp>
#include <ILoginHubFactory.hpp>

class MessengerAgent
{
public:
    MessengerAgent();
private:
    std::shared_ptr<ILoginHub> LoginHub_;
};