#ifndef RECEIVER_H
#define RECEIVER_H
#include <string.h>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio/buffer.hpp>
#include <map>
#include <queue>

typedef boost::shared_ptr<boost::lockfree::queue<std::string*, boost::lockfree::capacity<128>>>
    MSG_queue_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

typedef boost::shared_ptr<std::map<std::string, socket_ptr>> socket_map_ptr;

class receiver
{
   public:
    receiver (){};
    ~receiver (){};
    static int send ( std::string* msg, socket_ptr sock );
    static void loop ( MSG_queue_ptr messageQueue, socket_map_ptr smp);
    static bool auth ( const char* log, const char* pass );
};
//
#endif