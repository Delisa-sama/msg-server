#ifndef TYPES_H
#define TYPES_H
#include <string.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lockfree/queue.hpp>
#include <map>

typedef boost::shared_ptr<boost::lockfree::queue<std::string*, boost::lockfree::capacity<128>>>
    MSG_queue_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

// typedef boost::shared_ptr<std::map<std::string, std::pair<socket_ptr, bool>>> user_map_ptr;

//шаред птр на мэп юзеров
typedef boost::shared_ptr<std::multiset<boost::shared_ptr<User>>> user_map_ptr;
enum Status { Online = 1, Offline, NotAuth };
#endif