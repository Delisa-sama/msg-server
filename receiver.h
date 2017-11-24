#ifndef RECEIVER_H
#define RECEIVER_H
#include <Friends.h>
#include <types.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/thread/thread.hpp>
#include <list>
#include <queue>

class receiver
{
  public:
    receiver () {};
    ~receiver (){};
    static bool logout ( const char* log, user_map_ptr smp );
    static void login ( const char* log, user_map_ptr smp );
    static int send ( std::string* msg, socket_ptr sock );
    static void loop ( MSG_queue_ptr messageQueue, user_map_ptr smp );
};
//
#endif