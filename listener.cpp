#include <auth.h>
#include <getBlock.h>
#include <listener.h>
#include <logout.h>
#include <boost/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>

void listener::listen ( socket_ptr sock,
                        MSG_queue_ptr messageQueue,
                        user_map_ptr smp,
                        ptree_ptr ptree_ )
{
    char buff[256];  // 256 (DEBUG 8)
    int bytes;
    bool auth_flag = false;
    boost::system::error_code ec;

    while ( ec == 0 ) {
//        for ( int i = 0; i < 256; i++ ) {
//            buff[i] = '\0';
//        }

        bytes = sock->read_some ( boost::asio::buffer ( buff ), ec );
        buff[bytes + 1] = '\0';
        if ( bytes > 0 ) {
            std::cout << "readed" << std::endl;
            msg_ptr msg ( new std::string ( buff ) );
            std::cout << "DEBUG     " << ( buff ) << std::endl;
            if ( !auth_flag ) {
                std::cout << "DEBUG     "
                          << "putjson" << std::endl;
                // std::cout << *msg << std::endl;
                ptree_->put ( *( getBlock ( msg, 3 ) ), *( getBlock ( msg, 4 ) ) );
                auth_flag = true;

                std::cout << "DEBUG     "
                          << "auth " << *( getBlock ( msg, 3 ) ) << std::endl;
                auth_flag =
                    auth ( getBlock ( msg, 3 ), getBlock ( msg, 4 ), smp, sock, ptree_ );
            }

            messageQueue->push ( msg );
            std::cout << "DEBUG     " << ( *msg ) << "PUSHED" << std::endl;
        }
    }
    std::cout << "Disconnected" << std::endl;

    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        if ( ( it->get ()->getSock () ) == sock ) {
            it->get ()->getSock ()->close ();
            it->get ()->setStatus ( Offline );
            it->get ()->Notify_all ();
            break;
        }
    }

    sock->shutdown ( boost::asio::ip::tcp::socket::shutdown_both, ec );
    sock->close ();
}

void listener::handle_connections ( boost::asio::io_service* service,
                                    MSG_queue_ptr q,
                                    int port,
                                    user_map_ptr smp,
                                    ptree_ptr ptree_ )
{
    boost::thread_group listener_threads;
    while ( true ) {
        boost::asio::ip::tcp::acceptor acceptor (
            *service, boost::asio::ip::tcp::endpoint ( boost::asio::ip::tcp::v4 (), port ) );

        socket_ptr sock ( new boost::asio::ip::tcp::socket ( *service ) );
        std::cout << "Listen" << std::endl;

        acceptor.accept ( *sock );

        std::cout << "accepted" << std::endl;
        //        boost::property_tree::ptree* ptree_;
        listener_threads.create_thread (
            boost::bind ( listener::listen, sock, q, smp, ptree_ ) );
    }
    listener_threads.join_all ();

    return;
}
