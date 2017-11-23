#include <listener.h>
#include <receiver.h>
//#include <sh_queue.h>

// typedef boost::shared_ptr<listener> listener_ptr;
// typedef boost::shared_ptr<receiver> receiver_ptr;

class server
{
    socket_map_ptr smp ( new ( std::map<std::string, socket_ptr> ) );

   public:
    server (){};
    ~server (){};

    void run ();
    void stop ();
};