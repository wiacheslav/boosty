

#include "server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context &io_context, short port)
        : io_context_(io_context),
          acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    BOOST_LOG_TRIVIAL(info) << boost::format("Server started listening on port %1%") % port;
    start_accept();
}

void Server::start_accept() {
    Session *new_session = new Session(io_context_);
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&Server::handle_accept, this, new_session,
                                       boost::asio::placeholders::error));
}

void Server::handle_accept(Session *new_session,
                           const boost::system::error_code &error) {
    if (!error) {
        new_session->start();
    } else {
        BOOST_LOG_TRIVIAL(error) << boost::format("Error occurred: %1%") % error;
        delete new_session;
    }

    start_accept();
}

int main(int arg, char **argv) {

    boost::asio::io_context io_context;

    using namespace std; // For atoi.
    Server s(io_context, 4800);

    io_context.run();

    return 0;
}