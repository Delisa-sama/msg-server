#ifndef RECEIVER_H
#define RECEIVER_H
#include <types.h>
#include <Friends.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/thread/thread.hpp>
#include <list>
#include <queue>

class receiver
{
    boost::property_tree::ptree User_pTree;
    

   public:
    receiver () { boost::property_tree::read_json ( "Users.json", User_pTree ); };
    ~receiver (){};
    static bool logout(const char* log, user_map_ptr smp);
    static void login(const char* log, user_map_ptr smp);
    static int send ( std::string* msg, socket_ptr sock );
    static void loop ( MSG_queue_ptr messageQueue, user_map_ptr smp );
    static bool auth ( const char* log, const char* pass );
    static bool reg ( const char* log, const char* pass );
};
//
#endif