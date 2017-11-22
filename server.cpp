#include <server.h>

void serv::run ()
{
    try {
        boost::thread_group threads;
        boost::asio::io_service service;
        
        
        
        MSG_queue_ptr q (
            new ( boost::lockfree::queue<std::string*, boost::lockfree::capacity<128>> ) );
//smp сделать полем класса
        //socket_map_ptr smp ( new ( std::map<std::string, socket_ptr> ) );
        //sender* sender_= new sender;
        threads.create_thread (
            boost::bind ( listener::handle_connections, &service, q, 1488, smp ) );
        threads.create_thread ( boost::bind ( receiver::loop, q, smp ) );
        threads.join_all ();

    } catch ( std::exception& e ) {
        // std::cerr << e.what () << std::endl;
    }
}

void serv::stop () {
    int errCode = 0;
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        
        it->second->shutdown(boost::asio::ip::tcp::socket::shutdown_both, errCode);
        it->second->close();
        it->exclude();
        
    }
}