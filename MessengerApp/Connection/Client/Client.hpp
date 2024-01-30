#pragma once

#include <boost/asio.hpp>
#include <string>
#include <thread>

#include <Common/Logger.hpp>

namespace connection::client
{

class Client final
{
public:
    Client();
    void connect(const std::string& host, const std::string& port);
    void login(const std::string& username);
    void logout(const std::string& sender);
    void sendMessage(const std::string& sender, const std::string& recipient, const std::string& message);

    void run();
    void stop();

private:
    void readData();
    void sendData(const std::string& data);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
    std::string data_;
    std::mutex mtx_;
    Logger logger_;
};

} // namespace connection::client