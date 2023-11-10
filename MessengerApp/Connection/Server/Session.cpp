#include "Session.hpp"

Session::Session(boost::asio::ip::tcp::socket socket, std::map<std::string, std::shared_ptr<Session>>& sessions)
    : socket_(std::move(socket))
    , activeSessions_(sessions)
    , logger_("Session") {}

void Session::start()
{
    receive();
}

void Session::receive() {
    auto self(shared_from_this());
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(data_), '\n',
        [this, self](boost::system::error_code errorCode, std::size_t length)
        {
            if (!errorCode)
            {
                std::string line(data_.substr(0, length - 1));
                data_.erase(0, length);

                std::string type, sender, recipient, content;
                std::istringstream iss(line);
                std::getline(iss, type, '|');
                std::getline(iss, sender, '|');
                std::getline(iss, recipient, '|');
                std::getline(iss, content, '|');

                if (type == "CONNECT")
                {
                    logger_.log(Severity::info, "successfully established session with " + sender);
                    username_ = sender;
                    activeSessions_[username_] = self;
                } 
                else if (type == "DISCONNECT")
                {
                    logger_.log(Severity::info, "successfully closed session with " + sender);
                    activeSessions_.erase(username_);
                }
                else if (type == "MESSAGE")
                {
                    auto recipientSession = activeSessions_.find(recipient);
                    if (recipientSession != activeSessions_.end()) 
                    {
                        logger_.log(Severity::info, "got message from " + sender + ", forwarding message to " + recipient);
                        std::string forwardMessage = "MESSAGE|" + sender + "|" + recipient + "|" + content;
                        recipientSession->second->send(forwardMessage);
                    }
                    logger_.log(Severity::warning, "got message from " + sender + ", but recipient: " + recipient + " is offline");
                }
                logger_.log(Severity::warning, "received unknown protocol message, start retrying... ");
                receive();
            } 
            else 
            {
                logger_.log(Severity::warning, "connection lost");
                activeSessions_.erase(username_);
            }
        });
}

void Session::send(const std::string& data)
{
    auto self(shared_from_this());
    std::string response = "Hello, client! This is a custom response from the server.";
    boost::asio::async_write(socket_, boost::asio::buffer(response),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                receive();
            }
        });
}