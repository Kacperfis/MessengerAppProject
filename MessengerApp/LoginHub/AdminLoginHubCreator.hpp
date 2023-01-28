#pragma once
#include <ILoginHubFactory.hpp>
#include <ILoginHub.hpp>
#include "AdminLoginHub.hpp"
#include <memory>

class AdminLoginHubCreator : public ILoginHubFactory
{
public:
    std::shared_ptr<ILoginHub> createHub() const override;
};