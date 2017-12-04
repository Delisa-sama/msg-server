#include <auth.h>
#include <getBlock.h>
#include <getBlock.h>
#include <listener.h>
#include <boost/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>

void listener::listen ( socket_ptr sock,
                        MSG_queue_ptr messageQueue,
                        user_map_ptr smp,
                        boost::property_tree::ptree* ptree_ )
{
    char buff[256];  // 256 (DEBUG 8)
    int bytes;
    bool auth_flag = false;
    boost::system::error_code ec;

    while ( ec == 0 ) {
        bytes = sock->read_some ( boost::asio::buffer ( buff ), ec );

        if ( bytes > 0 ) {
            std::cout << "readed" << std::endl;
            std::string* msg = new std::string ( buff, 256 );
            
            if ( !auth_flag ) {
                try {
                    
                    std::cout << "readjson" << std::endl;
                    
                    boost::property_tree::read_json ( "Users.json", *ptree_ );
                } catch ( ... ) {
                    ptree_->clear();
                    std::cout << "putjson" << std::endl;
                    ptree_->put ( getBlock ( msg, 3 ), getBlock ( msg, 4 ) );
                    auth_flag = true;
                };
                
                std::cout << "auth" << std::endl;
                auth_flag =
                    auth ( getBlock ( msg, 3 ), getBlock ( msg, 4 ), smp, sock, ptree_ );
                messageQueue->push ( msg );
            } else {
                std::cout << *msg << "PUSHED" << std::endl;
                messageQueue->push ( msg );
            }
        } else {
            std::cout << "error" << std::endl;
        }
    }

    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        if ( ( it->get ()->getSock () ) == sock ) {
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
                                    boost::property_tree::ptree* ptree_ )
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
