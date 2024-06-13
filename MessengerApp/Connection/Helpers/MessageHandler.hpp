#pragma once

#include <memory>

#include "Message.hpp"
#include "Common/Logger.hpp"
#include <../MessengerInterfaces/IEncryptionManager.hpp>

namespace connection::helpers::message
{

class MessageHandler final
{
public:
    static void handleMessage(const Message& message, const std::shared_ptr<interface::IEncryptionManager>& encryptionManager) noexcept;
private:
    static void handleCheckAvailabilityMessage(const Message& message) noexcept;
    static void handleStandardMessage(const Message& message, const std::shared_ptr<interface::IEncryptionManager>& encryptionManager) noexcept;
};

} // namespace connection::helpers::message
