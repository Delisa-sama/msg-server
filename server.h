#include <listener.h>
#include <receiver.h>
//#include <sh_queue.h>

// typedef boost::shared_ptr<listener> listener_ptr;
// typedef boost::shared_ptr<receiver> receiver_ptr;

class server
{
    user_map_ptr smp ( new std::multiset<boost::shared_ptr<User>> );

   public:
    server (){};
    ~server (){};

    void run ();
    void stop ();
};