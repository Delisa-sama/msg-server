#include <listener.h>
#include <receiver.h>
//#include <sh_queue.h>

// typedef boost::shared_ptr<listener> listener_ptr;
// typedef boost::shared_ptr<receiver> receiver_ptr;

class serv
{
    // queue_ptr MSG_queue;//(new sh_queue());
    // listener_ptr SHListener;//(new listener(1488));
    // receiver_ptr SHReceiver;//(new receiver());
    socket_map_ptr smp;

   public:
    serv (){smp.reset ( new ( std::map<std::string, socket_ptr> ) );};
    ~serv (){};

    void run ();
    void stop ();
};