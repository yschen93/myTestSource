//
// Created by 谭鑫 on 2022/9/28.
//
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <ctime>
#include <memory>
#include <boost/bind/bind.hpp>
using namespace boost::asio;

std::string echo_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

class tcp_connection : public std::enable_shared_from_this<tcp_connection>
{
public:
    typedef std::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io)
    {
        //return std::make_shared<tcp_connection>(io);
        return pointer(new tcp_connection(io));
    }

    boost::asio::ip::tcp::socket& socket()
    {
        return sock_;
    }

    void start()
    {
        std::string message = echo_string();
        boost::asio::async_write(sock_, boost::asio::buffer(message),
            boost::bind(&tcp_connection::write_handler, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void write_handler(const boost::system::error_code& ec, size_t bytes_transferred)
    {

    }

private:
    tcp_connection(boost::asio::io_context& io)
    :sock_(io)
    {

    }
    boost::asio::ip::tcp::socket sock_;
};

class tcp_server
{
public:
    tcp_server(boost::asio::io_context& io)
    :io_(io)
    ,acceptor_(io, ip::tcp::endpoint(ip::tcp::v4(), 13)) //bind listen
    {
        start_accept();
    }

    void start_accept()
    {
        tcp_connection::pointer new_connection =
                tcp_connection::create(io_);

        acceptor_.async_accept(new_connection->socket(), boost::bind(&tcp_server::acceptor_handler, this,
            new_connection, boost::asio::placeholders::error));
    }

    void acceptor_handler(tcp_connection::pointer new_connection, const boost::system::error_code& ec) //为什么这里必须用const &或者 拷贝
    {
        new_connection->start();
    }
private:
    boost::asio::io_context& io_; //这里必须用引用
    ip::tcp::acceptor acceptor_;
};

int main(int argc, char *argv[])
{
    boost::asio::io_context io;
    tcp_server server(io);
    io.run();
    return 0;
}