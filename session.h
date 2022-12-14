#ifndef BOOSTY_SESSION_H
#define BOOSTY_SESSION_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

using boost::asio::ip::tcp;

class Session {
public:
    Session(boost::asio::io_context &io_context) :
            socket_(io_context) {
    }
    tcp::socket &socket();
    void start();
private:
    void handle_read(const boost::system::error_code &error,
                     size_t bytes_transferred);

    void handle_write(const boost::system::error_code &error);

    tcp::socket socket_;

    enum {
        max_length = (1024 * 1024 * 128) // 128MB
    };

    boost::array<float, max_length> data_;
    //char data_[1024];
};


#endif //BOOSTY_SESSION_H
