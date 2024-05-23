#pragma once
#include <memory>

#include <ILoginHubFactory.hpp>
#include <ILoginHub.hpp>
#include "UserLoginHub.hpp"

namespace login
{

class UserLoginHubCreator : public interface::ILoginHubFactory
{
public:
    std::shared_ptr<interface::ILoginHub> createHub() const override;
};

} // namespace login
