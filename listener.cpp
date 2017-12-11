#include <listener.h>
#include <iostream>

void listener::listen (socket_ptr sock,
                       MSG_queue_ptr messageQueue,
                       user_map_ptr smp,
                       ptree_ptr ptree_)
{
    int bytes;
    boost::system::error_code ec;
		
    while (ec == 0) {
        char buff[MSG_LEN] = {'\0'};

        bytes = sock->read_some (boost::asio::buffer (buff), ec);

        if (bytes > 0) {
            msg_ptr msg (new std::string (buff));
#ifdef DEBUG
            std::cout << buff << std::endl;
#endif
            if (static_cast<int> (buff[MSG_TYPE_POS]) == types::log) {
                ptree_->put (*(get_token (msg, types::Login)),
                             *(get_token (msg, types::Data)));

                auth (get_token (msg, types::Login),
                      get_token (msg, types::Data), smp, sock, ptree_);
            }
            messageQueue->push (msg);
        }
    }

    for (auto it = smp->begin (); it != smp->end (); ++it) {
        if ((it->get ()->getSock ()) == sock) {
            it->get ()->getSock ()->close ();
            it->get ()->setStatus (types::Offline);
            it->get ()->Notify_all ();
            break;
        }
    }

    sock->shutdown (boost::asio::ip::tcp::socket::shutdown_both, ec);
    sock->close ();
}

void listener::handle_connections (boost::asio::io_service* service,
                                   MSG_queue_ptr q,
                                   int port,
                                   user_map_ptr smp,
                                   ptree_ptr ptree_,
                                   bool* flag,
                                   boost::thread_group* listener_threads)
{
    while (*flag) {
        boost::asio::ip::tcp::acceptor acceptor (
            *service,
            boost::asio::ip::tcp::endpoint (boost::asio::ip::tcp::v4 (), port));

        socket_ptr sock (new boost::asio::ip::tcp::socket (*service));
#ifdef DEBUG
        std::cout << "Waiting new user" << std::endl;
#endif
        acceptor.accept (*sock);

        listener_threads->create_thread (
            boost::bind (listener::listen, sock, q, smp, ptree_));
    }

    return;
}
