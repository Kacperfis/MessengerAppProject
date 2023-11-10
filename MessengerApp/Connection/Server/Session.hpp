#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string> 
#include <iostream>

#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::ip::tcp::socket socket, std::map<std::string, std::shared_ptr<Session>>& sessions);
    void start();
private:
    void send(const std::string& data);
    void receive();

    std::map<std::string, std::shared_ptr<Session>>& activeSessions_;
    boost::asio::ip::tcp::socket socket_;
    std::string data_;
    std::string username_;   
};