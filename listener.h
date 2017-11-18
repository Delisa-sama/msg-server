#ifndef LISTENER_H
#define LISTENER_H
#include <string.h>
#include <boost/asio.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>
#include <list>
#include <map>
#include <queue>
#include <system_error>

// using boost;

// typedef boost::shared_ptr<sh_queue> queue_ptr;
typedef boost::shared_ptr<boost::lockfree::queue<std::string*, boost::lockfree::capacity<128>>>
    MSG_queue_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

typedef boost::shared_ptr<std::map<std::string, socket_ptr>> socket_map_ptr;

class listener
{
    // std::list<boost::thread> threads_list;
    // boost::lockfree::queue<boost::thread> threads_queue;
   public:
    static void listen ( socket_ptr sock, MSG_queue_ptr messageQueue, socket_map_ptr smp );
    static size_t read_complete ( char* buff, boost::system::error_code& err, size_t bytes );
    listener (){};
    ~listener (){};
    static void handle_connections ( boost::asio::io_service* service,
                                     MSG_queue_ptr q,
                                     int port,
                                     socket_map_ptr smp );
};
#endif
