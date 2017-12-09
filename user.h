#ifndef USER_H
#define USER_H
#include <types.h>
#include <list>

class User
{
   public:
    User (msg_ptr Log, msg_ptr Pass, socket_ptr sock_, types::Status status_);
    ~User ();

    std::string getLogin () { return Login; }
    std::string getPass () { return Password; }
    socket_ptr getSock () { return sock; }
    types::Status getStatus () { return status; };
    void setStatus (types::Status status_) { status = status_; }
    void addFriend (socket_ptr Friend) { Friends->insert (Friend); }
    std::set<socket_ptr>* getFriends () { return Friends; }
    void Notify_all ();

   private:
    std::string Login;
    std::string Password;
    socket_ptr sock;
    types::Status status;
    std::set<socket_ptr>* Friends;
};

typedef boost::shared_ptr<std::list<boost::shared_ptr<User>>> user_map_ptr;
#endif  // USER_H
