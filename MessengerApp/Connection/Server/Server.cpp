#include "Server.hpp"

Server::Server()
    : acceptor_(ioContext_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080))
    , logger_("Server") {}

void Server::acceptConnection()
{
    acceptor_.async_accept(
    [this](boost::system::error_code errorCode, boost::asio::ip::tcp::socket socket)
    {
        if (!errorCode)
        {
            auto session = std::make_shared<Session>(std::move(socket), activeSessions_);
            session->start();
        }
        acceptConnection();
    });
}

void Server::start()
{
    std::cout << "Server started on port 8080" << std::endl;
    acceptConnection();
    ioContext_.run();
}

void Server::stop()
{
    ioContext_.stop();
    std::cout << "Server stopped" << std::endl;
}