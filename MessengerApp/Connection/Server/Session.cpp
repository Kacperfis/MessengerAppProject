#include "Session.hpp"

Session::Session(boost::asio::ip::tcp::socket socket, std::map<std::string, std::shared_ptr<Session>>& sessions)
    : socket_(std::move(socket))
    , activeSessions_(sessions) {}


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

                if (type == "ESTABLISH")
                {
                    std::cout << "successfully established session with " + sender << std::endl;
                    username_ = sender;
                    activeSessions_[username_] = self;

                    std::set<std::string> activeUsersSet;
                    for (const auto& pair : activeSessions_) activeUsersSet.insert(pair.first);
                    for (const auto& pair : activeSessions_)
                    {
                        auto activeUsers = getActiveUsers(activeUsersSet, pair.first);
                        std::cout << "forwarding check availability message to " + pair.first << std::endl;
                        std::string forwardMessage = "CHECK_AVAILABILITY|" + sender + "|" + pair.first + "|" + activeUsers;
                        pair.second->send(forwardMessage);
                    }
                } 
                else if (type == "RELINQUISH")
                {
                    std::cout << "successfully closed session with " + sender << std::endl;
                    std::cout << "username_: " << username_ << std::endl;
                    activeSessions_.erase(username_);
                }
                else if (type == "MESSAGE")
                {
                    auto recipientSession = activeSessions_.find(recipient);
                    if (recipientSession != activeSessions_.end()) 
                    {
                        std::cout << "got message from " + sender + ", forwarding message to " + recipient << std::endl;
                        std::string forwardMessage = "MESSAGE|" + sender + "|" + recipient + "|" + content;
                        recipientSession->second->send(forwardMessage);
                    }
                    else std::cout << "got message from " + sender + ", but recipient: " + recipient + " is offline" << std::endl;
                }
                else std::cout << "received unknown protocol message, start retrying... " << std::endl;
                receive();
            } 
            else
            {
                std::cout << "connection lost" << std::endl;
                activeSessions_.erase(username_);
            }
        });
}

std::string Session::getActiveUsers(const std::set<std::string>& activeUsers, const std::string& username)
{
    std::string result;
    auto activeUsersCopy = activeUsers;
    auto it = activeUsersCopy.find(username);
    if (it != activeUsersCopy.end())
    {
        activeUsersCopy.erase(it);
    }
    for (auto activeUser : activeUsersCopy)
    {
        result += activeUser + ",";
    }

    if (!result.empty() && result.back() == ',')
    {
        result.erase(result.length() - 1);
    }

    return result;
}

void Session::send(const std::string& data)
{
    std::cout << "About to send to " << username_ << ": " << data << std::endl;

    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data + "\n"),
        [this, self, data](boost::system::error_code errorCode, std::size_t length) {
            if (errorCode) {
                std::cerr << "Error sending to " << username_ << ": " << errorCode.message() << std::endl;
            } else {
                std::cout << "Sent " << length << " bytes to " << username_ << ": " << data << std::endl;
            }
        });
}
