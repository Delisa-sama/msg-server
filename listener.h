#ifndef LISTENER_H
#define LISTENER_H
#include <User.h>
#include <types.h>
#include <boost/asio.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>
#include <system_error>
#include <Shared_queue.h>

class listener
{
   public:
    static void listen ( socket_ptr sock,
                         MSG_queue_ptr messageQueue,
                         user_map_ptr smp,
                         ptree_ptr ptree_ );
    listener (){};
    ~listener (){};
    static void handle_connections ( boost::asio::io_service* service,
                                     MSG_queue_ptr q,
                                     int port,
                                     user_map_ptr smp,
                                     ptree_ptr ptree_ );
};
#endif
