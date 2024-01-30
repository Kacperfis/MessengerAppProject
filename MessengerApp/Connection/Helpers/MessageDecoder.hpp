#pragma once

#include "Message.hpp"

#include <string>

namespace connection::helpers::message
{

class MessageDecoder
{
public:
    static Message decodeMessage(const std::string& message) noexcept;
};

} // namespace connection::helpers::message