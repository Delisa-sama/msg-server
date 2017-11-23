#ifndef USER_H
#define USER_H
#include <types.h>

class User
{
    std::string Login;
    std::string Password;
    socket_ptr sock;
    Status status;
    std::set<socket_ptr> Friends;

   public:
    User ( std::string* Log, std::string* Pass, socket_ptr sock_, Status status_ );
    ~User ();

    const std::string* getLogin (){return const_cast<std::string*> & Login};
    const std::string* getPass (){return const_cast<std::string*> & Password};
    socket_ptr getSock (){return sock};
    Status getStatus (){return status};
    void setStatus ( Status status_ );
    void addFriend ( User* Friend ) { Friends.insert ( *Friend ); };
    void Notify_all ();
}
#endif