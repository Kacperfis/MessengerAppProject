#include "AdminLoginHubCreator.hpp"
#include <memory>

std::shared_ptr<ILoginHub> AdminLoginHubCreator::createHub() const
{
    return std::make_shared<AdminLoginHub>();
}