#pragma once

#include "Message.hpp"
#include "Common/Logger.hpp"

#include <Encryption/EncryptionManager.hpp>

namespace connection::helpers::message
{

class MessageHandler final
{
public:
    static void handleMessage(const Message& message, const std::shared_ptr<encryption::EncryptionManager>& encryptionManager) noexcept;
private:
    static void handleCheckAvailabilityMessage(const Message& message) noexcept;
    static void handleStandardMessage(const Message& message, const std::shared_ptr<encryption::EncryptionManager>& encryptionManager) noexcept;
};

} // namespace connection::helpers::message
