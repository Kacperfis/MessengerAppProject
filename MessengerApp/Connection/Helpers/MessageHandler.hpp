#pragma once

#include "Message.hpp"
#include "Common/Logger.hpp"

namespace connection::helpers::message
{

class MessageHandler final
{
public:
    static void handleMessage(const Message& message) noexcept;
private:
    static void handleCheckAvailabilityMessage(const Message& message) noexcept;
    static void handleStandardMessage(const Message& message) noexcept;
};

} // namespace connection::helpers::message
