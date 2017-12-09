#ifndef LISTENER_H
#define LISTENER_H
#include <acts.h>
#include <get_token.h>
#include <shared_queue.h>
#include <boost/asio.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>
#include <system_error>

class listener
{
   public:
    static void listen (socket_ptr sock,
                        MSG_queue_ptr messageQueue,
                        user_map_ptr smp,
                        ptree_ptr ptree_);
    listener () {}
    ~listener () {}
    static void handle_connections (boost::asio::io_service* service,
                                    MSG_queue_ptr q,
                                    int port,
                                    user_map_ptr smp,
                                    ptree_ptr ptree_,
                                    bool* flag,
                                    boost::thread_group* listener_threads);
};
#endif  // LISTENER_H
