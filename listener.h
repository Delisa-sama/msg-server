#ifndef LISTENER_H
#define LISTENER_H
#include <types.h>
#include <boost/asio.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>
#include <list>
#include <queue>
#include <system_error>

    class listener
{
    // std::list<boost::thread> threads_list;
    // boost::lockfree::queue<boost::thread> threads_queue;
   public:
    static void listen ( socket_ptr sock, MSG_queue_ptr messageQueue, user_map_ptr smp );
    static size_t read_complete ( char* buff, boost::system::error_code& err, size_t bytes );
    listener (){};
    ~listener (){};
    static void handle_connections ( boost::asio::io_service* service,
                                     MSG_queue_ptr q,
                                     int port,
                                     user_map_ptr smp );
};
#endif
