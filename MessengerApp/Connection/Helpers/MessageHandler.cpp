#include "MessageHandler.hpp"

#include <vector>
#include <iostream>
#include <memory>

namespace connection::helpers::message
{

void MessageHandler::handleMessage(const Message& message, const std::shared_ptr<EncryptionManager>& encryptionManager) noexcept
{
    Logger logger("MessageHandler");
    logger.log(Severity::info, "handling message with messageType: " + toString(message.messageType));
    switch (message.messageType)
    {
        case MessageType::CHECK_AVAILABILITY:
        {
            handleCheckAvailabilityMessage(message);
            break;
        }
        case MessageType::MESSAGE:
        {
            handleStandardMessage(message, encryptionManager);
            break;
        }
    }
}

void MessageHandler::handleCheckAvailabilityMessage(const Message& message) noexcept
{
    if (message.sender != message.recipient)
    {
        std::cout << "[INFO] " << message.sender << " has joined to the chat" << std::endl;
    }
    if (message.contentSize-1 == 0)
    {
        std::cout << "[INFO] there are no active users" << std::endl;
    }
    else
    {
        std::cout << "[INFO] current active users: " << message.content << std::endl;
    }
}

void MessageHandler::handleStandardMessage(const Message& message, const std::shared_ptr<EncryptionManager>& encryptionManager) noexcept
{
    std::cout << "[" << message.sender << "]: " << encryptionManager->decryptString(message.content) << std::endl;
}

} // namespace connection::helpers::message
