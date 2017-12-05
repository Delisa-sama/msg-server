#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H
#include <types.h>
#include <mutex>
#include <queue>
class Shared_queue
{
    std::mutex mutex_;
    std::queue<std::string> data;

   public:
    Shared_queue (){};
    ~Shared_queue (){};
    void push ( msg_ptr msg );
    msg_ptr pop ();
    bool empty () { return data.empty (); };
};
typedef boost::shared_ptr<Shared_queue> MSG_queue_ptr;
#endif