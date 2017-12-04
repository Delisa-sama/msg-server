#ifndef RECEIVER_H
#define RECEIVER_H
#include <User.h>
#include <types.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/thread/thread.hpp>
#include <list>
#include <queue>

class receiver
{
   public:
    receiver (){};
    ~receiver (){};
    static void loop ( MSG_queue_ptr messageQueue,
                       user_map_ptr smp,
                       ptree_ptr ptree_ );
};
//
#endif