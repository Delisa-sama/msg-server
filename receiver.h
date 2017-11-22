#ifndef RECEIVER_H
#define RECEIVER_H
#include <string.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/thread/thread.hpp>
#include <list>
#include <map>
#include <queue>

typedef boost::shared_ptr<boost::lockfree::queue<std::string*, boost::lockfree::capacity<128>>>
    MSG_queue_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

typedef boost::shared_ptr<std::map<std::string, socket_ptr, bool>> user_map_ptr;

typedef std::map << std::string, std::map<std::string>> monitored_user_list;

class receiver
{
    boost::property_tree::ptree UserList;
    monitored_user_list mul;

   public:
    receiver () { boost::property_tree::read_json ( "UserList.json", UserList ); };
    ~receiver (){};
    static int send ( std::string* msg, socket_ptr sock );
    static void loop ( MSG_queue_ptr messageQueue, user_map_ptr smp );
    static bool auth ( const char* log, const char* pass );
};
//
#endif