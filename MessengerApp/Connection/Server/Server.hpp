#pragma once

#include <iostream>
#include <string>

#include "Session.hpp"
#include <boost/asio.hpp>

class Server
{
public:
    Server();
    void start();
    void stop();
private:
    void acceptConnection();

    boost::asio::io_context ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::map<std::string, std::shared_ptr<Session>> activeSessions_;
};