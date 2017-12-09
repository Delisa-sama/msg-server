#ifndef SERVER_H
#define SERVER_H
#include <listener.h>
#include <receiver.h>

class server
{
   public:
    server (int port_)
    {
        smp.reset (new (std::list<boost::shared_ptr<User>>));
        port = port_;
        flag = true;
    };
    ~server (){};

    void run ();
    void stop ();
    bool get_flag () { return flag; };
   private:
    bool flag;
    int port;
    user_map_ptr smp;
};
#endif  // SERVER_H
