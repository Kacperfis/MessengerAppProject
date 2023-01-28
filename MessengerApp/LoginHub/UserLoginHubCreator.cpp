#include "UserLoginHubCreator.hpp"

std::shared_ptr<ILoginHub> UserLoginHubCreator::createHub() const
{
    return std::make_shared<UserLoginHub>();
}
