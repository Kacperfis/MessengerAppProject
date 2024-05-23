#pragma once
#include <memory>

#include <ILoginHubFactory.hpp>
#include <ILoginHub.hpp>
#include "AdminLoginHub.hpp"

namespace login
{

class AdminLoginHubCreator : public interface::ILoginHubFactory
{
public:
    std::shared_ptr<interface::ILoginHub> createHub() const override;
};

} // namespace login
