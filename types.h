#ifndef TYPES_H
#define TYPES_H
#include <string.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <list>
#include <set>



typedef boost::shared_ptr<boost::lockfree::queue<std::string*, boost::lockfree::capacity<128>>>
    MSG_queue_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

// typedef boost::shared_ptr<std::map<std::string, std::pair<socket_ptr, bool>>> user_map_ptr;
enum Status { Online = 0, Offline, NotAuth };
#endif