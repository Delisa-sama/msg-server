#ifndef TYPES_H
#define TYPES_H
#include <string.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <set>

typedef boost::shared_ptr<std::string> msg_ptr;
typedef boost::shared_ptr<boost::property_tree::ptree> ptree_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

enum Status { Online = 0, Offline, NotAuth };
#endif