#include <listener.h>
#include <receiver.h>

class server
{
    user_map_ptr smp;

   public:
    server () { smp.reset ( new ( std::list<boost::shared_ptr<User>> ) ); };
    ~server (){};

    void run ();
    void stop ();
};