#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include "Session.hpp"
#include "Common/Logger.hpp"

namespace connection::server
{

class Server final
{
public:
    Server();
    void start();
    void stop();
private:
    void acceptConnection();

    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::map<std::string, std::shared_ptr<session::Session>> activeSessions_;
    Logger logger_;
};

} // namespace connection::server
