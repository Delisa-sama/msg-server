#ifndef RECEIVER_H
#define RECEIVER_H
#include <User.h>
#include <types.h>
#include <Shared_queue.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/thread/thread.hpp>

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