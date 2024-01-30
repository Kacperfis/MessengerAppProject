#pragma once

#include "Message.hpp"

namespace connection::helpers::message
{

class MessageHandler
{
public:
    static void handleMessage(const Message& message) noexcept;
private:
    static void handleCheckAvailabilityMessage(const Message& message) noexcept;
    static void handleStandardMessage(const Message& message) noexcept;
};

} // namespace connection::helpers::message