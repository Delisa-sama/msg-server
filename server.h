#ifndef SERVER_H
#define SERVER_H
#include <listener.h>
#include <receiver.h>

class server
{
   public:
    server () { smp.reset (new (std::list<boost::shared_ptr<User>>)); };
    ~server (){};

    void run ();
    void stop ();

   private:
    user_map_ptr smp;
};
#endif