#pragma once

#include <ILoginHub.hpp>
#include <memory>

class ILoginHubFactory
{
public:
    virtual ~ILoginHubFactory(){};
    virtual std::shared_ptr<ILoginHub> createHub() const = 0;
};