#include "AdminLoginHubCreator.hpp"

std::shared_ptr<ILoginHub> AdminLoginHubCreator::createHub() const
{
    return std::make_shared<AdminLoginHub>();
}