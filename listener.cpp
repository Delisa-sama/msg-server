#include <listener.h>
#include <boost/bind.hpp>
#include <iostream>
#include <getBlock.h>

void listener::listen ( socket_ptr sock, MSG_queue_ptr messageQueue, user_map_ptr smp )
{
    char buff[256];  // 256 (DEBUG 8)
    int bytes;
    
    while ( true ) {
        
        bytes = sock->read_some ( boost::asio::buffer ( buff ) );

        if ( bytes > 0 ) {
            
            std::cout << "readed" << std::endl;
            std::string* msg = new std::string ( buff, bytes );
            messageQueue->push ( msg );

            std::string login = getBlock ( *msg, 3 );
            smp->insert ( std::pair<std::string, socket_ptr> ( login, sock ) );
            
        } else {
            std::cout << "error" << std::endl;
        }
    }
}

void listener::handle_connections ( boost::asio::io_service* service,
                                    MSG_queue_ptr q,
                                    int port,
                                    user_map_ptr smp )
{
    
    boost::thread_group listener_threads;
    while ( true ) {
        boost::asio::ip::tcp::acceptor acceptor (
            *service, boost::asio::ip::tcp::endpoint ( boost::asio::ip::tcp::v4 (), port ) );

        socket_ptr sock ( new boost::asio::ip::tcp::socket ( *service ) );
        std::cout << "Listen" << std::endl;
        acceptor.accept ( *sock );

        std::cout << "accepted" << std::endl;

        listener_threads.create_thread ( boost::bind ( listener::listen, sock, q, smp ) );
    }
    listener_threads.join_all ();

    return;
}
