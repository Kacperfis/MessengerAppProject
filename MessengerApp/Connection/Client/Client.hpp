#pragma once

#include <boost/asio.hpp>
#include <string>
#include <thread>

class Client
{
public:
    Client();
    void connect(const std::string& host, const std::string& port);
    void login(const std::string& username);
    void sendMessage(const std::string& sender, const std::string& recipient, const std::string& message);
    void checkDataAvailability();
    void logout();
    void run();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    std::string data_;
    std::mutex mtx_;

    void readData();
    void sendData(const std::string& data);
};