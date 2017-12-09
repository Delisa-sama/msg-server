#ifndef TYPES_H
#define TYPES_H
#include <string.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <set>

#define MSG_LEN 256
#define MSG_TYPE_POS 5
#define MSG_ID_LEN 4

#define LOG_LEN 16
#define PASS_LEN 16

typedef boost::shared_ptr<std::string> msg_ptr;
typedef boost::shared_ptr<boost::property_tree::ptree> ptree_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
namespace types
{
enum msgType {

    log = 1,
    reg = 2,
    iex = 4,
    ion = 8,
    msg = 16

};

enum Tokens { ID = 1, Type = 2, Login = 3, Data = 4, Sender = 5 };

enum Status { Online = 0, Offline, NotAuth };
}

#endif  // TYPES_H
