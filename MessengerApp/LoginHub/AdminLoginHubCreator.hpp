#pragma once
#include <memory>

#include <ILoginHubFactory.hpp>
#include <ILoginHub.hpp>
#include "AdminLoginHub.hpp"

class AdminLoginHubCreator : public ILoginHubFactory
{
public:
    std::shared_ptr<ILoginHub> createHub() const override;
};
