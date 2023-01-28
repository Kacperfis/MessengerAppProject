#pragma once
#include <memory>

#include <ILoginHubFactory.hpp>
#include <ILoginHub.hpp>
#include "UserLoginHub.hpp"

class UserLoginHubCreator : public ILoginHubFactory
{
public:
    std::shared_ptr<ILoginHub> createHub() const override;
};
