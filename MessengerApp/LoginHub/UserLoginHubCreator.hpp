#pragma once
#include <ILoginHubFactory.hpp>
#include <ILoginHub.hpp>
#include "UserLoginHub.hpp"
#include <memory>

class UserLoginHubCreator : public ILoginHubFactory
{
public:
    std::shared_ptr<ILoginHub> createHub() const override;
};