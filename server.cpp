#include <server.h>

void server::run ()
{
    try {
        boost::thread_group threads;
        boost::asio::io_service service;

        MSG_queue_ptr q (
            new ( boost::lockfree::queue<std::string*, boost::lockfree::capacity<128>> ) );
        // smp сделать полем класса
        // socket_map_ptr smp ( new ( std::map<std::string, socket_ptr> ) );
        // sender* sender_= new sender;
        ptree_ptr ptree_ ( new boost::property_tree::ptree );
        try {
            //boost::property_tree::read_json ( "Users.json", *ptree_ );

        } catch ( ... ) {
            ptree_->clear ();
        };
        threads.create_thread (
            boost::bind ( listener::handle_connections, &service, q, 1488, smp, ptree_ ) );
        threads.create_thread ( boost::bind ( receiver::loop, q, smp, ptree_ ) );
        threads.join_all ();

    } catch ( std::exception& e ) {
        // std::cerr << e.what () << std::endl;
    }
}

void server::stop ()
{
    boost::system::error_code errCode;
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        it->get ()->getSock ()->shutdown ( boost::asio::ip::tcp::socket::shutdown_both,
                                           errCode );
        it->get ()->getSock ()->close ();
    }
}