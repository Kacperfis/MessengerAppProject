#include "Client.hpp"
#include <iostream>
#include <thread>

#include "Connection/Helpers/Message.hpp"
#include "Connection/Helpers/MessageDecoder.hpp"
#include "Connection/Helpers/MessageHandler.hpp"

namespace connection::client
{

Client::Client() :
    socket_(io_context_),
    resolver_(io_context_),
    encryptionManager_(std::make_shared<EncryptionManager>("", "0123456789abcdef0123456789abcdef", "0123456789abcdef")),
    logger_("Client") {}

void Client::connect(const std::string& host, const std::string& port)
{
    boost::asio::ip::tcp::resolver resolver(io_context_);
    boost::asio::connect(socket_, resolver.resolve(host, port));
    readData();
}

void Client::readData()
{
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(data_), '\n',
        [this](boost::system::error_code errorCode, std::size_t length)
        {
            if (!errorCode)
            {
                logger_.log(Severity::info, "received " + std::to_string(length) + " bytes of data");
                std::string message(data_.substr(0, length));

                logger_.log(Severity::info, "received message: " + message);
                auto decodedMessage = helpers::message::MessageDecoder::decodeMessage(message);
                helpers::message::MessageHandler::handleMessage(decodedMessage, encryptionManager_);
                data_.erase(0, length);
                readData();
            }
            else if (errorCode == boost::asio::error::operation_aborted)
            {
                logger_.log(Severity::warning, "read operation was cancelled");
            }
            else
            {
                logger_.log(Severity::warning, "read operation failed with error: " + errorCode.message());
            }
        }
    );
}

void Client::sendData(const std::string& data)
{
    logger_.log(Severity::info, "sending " + data);
    boost::asio::write(socket_, boost::asio::buffer(data + "\n"));
}

void Client::login(const std::string& username)
{
    sendData("ESTABLISH|" + username + "||");
}

void Client::sendMessage(const std::string& sender, const std::string& recipient, const std::string& message)
{
    sendData("MESSAGE|" + sender + "|" + recipient + "|" + encryptionManager_->encryptString(message));
}

void Client::logout(const std::string& sender)
{
    sendData("RELINQUISH|" + sender + "||");
}

void Client::run()
{
    logger_.log(Severity::info, "client started");
    std::lock_guard<std::mutex> lockGuard(mtx_);
    while (socket_.is_open() && !io_context_.stopped())
    {
        io_context_.restart();
        io_context_.run();
        if (io_context_.stopped())
        {
            break;
        }
    }
}

void Client::stop()
{
    if (socket_.is_open())
    {
        boost::system::error_code errorCode;
        socket_.close(errorCode);
        if (errorCode)
        {
            logger_.log(Severity::error, "Error on socket close during disconnect: " + errorCode.message());
            std::cerr << "Error on socket close during disconnect: " << errorCode.message() << std::endl;
        }
    }
}

} // namespace connection::client
