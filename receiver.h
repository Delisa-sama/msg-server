#ifndef RECEIVER_H
#define RECEIVER_H
#include <acts.h>
#include <get_token.h>
#include <shared_queue.h>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

class receiver
{
   public:
    receiver () {}
    ~receiver () {}
    static void loop (MSG_queue_ptr messageQueue,
                      user_map_ptr smp,
                      ptree_ptr ptree_);
};

#endif  // RECEIVER_H
