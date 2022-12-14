#ifndef BOOSTY_SERVER_H
#define BOOSTY_SERVER_H
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

#include "session.h"

class Server {
public:
    Server(boost::asio::io_context &io_context, short port);

private:
    void start_accept();
    void handle_accept(Session* new_session,const boost::system::error_code& error);
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;

};


#endif //BOOSTY_SERVER_H
