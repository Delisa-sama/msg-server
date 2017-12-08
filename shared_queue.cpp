#include <shared_queue.h>

msg_ptr Shared_queue::pop ()
{
    while (mutex_.try_lock ()) {
    };
    msg_ptr msg (new std::string (data.front ()));
    data.pop ();
    mutex_.unlock ();
    return msg;
}
void Shared_queue::push (msg_ptr msg)
{
    while (mutex_.try_lock ()) {
    };
    data.push (*msg);
    mutex_.unlock ();
}