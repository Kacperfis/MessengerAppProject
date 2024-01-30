#include "Client.hpp"
#include <iostream>
#include <thread>

#include "Connection/Helpers/Message.hpp"
#include "Connection/Helpers/MessageDecoder.hpp"
#include "Connection/Helpers/MessageHandler.hpp"

namespace connection::client
{

Client::Client() : socket_(io_context_), resolver_(io_context_)
{
}

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
                std::cout << "[Client] Data received: " << length << " bytes." << std::endl;
                std::string message(data_.substr(0, length));
                std::cout << "[Client] Message received: " << message << std::endl;
                auto decodedMessage = helpers::message::MessageDecoder::decodeMessage(message);
                std::cout << decodedMessage << std::endl;
                helpers::message::MessageHandler::handleMessage(decodedMessage);
                data_.erase(0, length);
                readData();
            }
            else if (errorCode == boost::asio::error::operation_aborted)
            {
                std::cout << "[Client] Read operation was canceled." << std::endl;
            }
            else
            {
                std::cerr << "[Client] Read failed: " << errorCode.message() << std::endl;
            }
        }
    );
}

void Client::sendData(const std::string& data)
{
    std::cout << "Sending: " << data << std::endl;
    boost::asio::write(socket_, boost::asio::buffer(data + "\n"));
}

void Client::login(const std::string& username)
{
    sendData("ESTABLISH|" + username + "||");
}

void Client::sendMessage(const std::string& sender, const std::string& recipient, const std::string& message)
{
    sendData("MESSAGE|" + sender + "|" + recipient + "|" + message);
}

void Client::logout(const std::string& sender)
{
    sendData("RELINQUISH|" + sender + "||");
}

void Client::run()
{
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
        boost::system::error_code ec;
        socket_.close(ec);
        if (ec)
        {
            std::cerr << "Error on socket close during disconnect: " << ec.message() << std::endl;
        }
    }
}

} // namespace connection::client