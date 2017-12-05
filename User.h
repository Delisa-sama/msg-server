#ifndef USER_H
#define USER_H
#include <types.h>
#include <list>

class User
{
    std::string Login;
    std::string Password;
    socket_ptr sock;
    Status status;
    std::set<socket_ptr>* Friends;

   public:
    User ( msg_ptr Log, msg_ptr Pass, socket_ptr sock_, Status status_ );
    ~User ();

    std::string getLogin () { return Login; };
    std::string getPass () { return Password ; };
    socket_ptr getSock () { return sock; };
    Status getStatus () { return status; };
    void setStatus ( Status status_ ) { status = status_; };
    void addFriend ( socket_ptr Friend ) { Friends->insert ( Friend ); };
    std::set<socket_ptr>* getFriends () { return Friends; }
    void Notify_all ();
};

typedef boost::shared_ptr<std::list<boost::shared_ptr<User>>> user_map_ptr;
#endif