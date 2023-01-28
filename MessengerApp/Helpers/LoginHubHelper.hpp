#pragma once
#include <memory>

#include <LoginHub/LoginData.hpp>

namespace helpers
{

std::unique_ptr<LoginData> login(std::istream& stdInput);

}  // namespace helpers