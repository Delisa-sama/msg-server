#include <User.h>

User::User(std::string* Log, std::string* Pass, socket_ptr sock_, Status status_)
{
    
    Login = *Log;
    Password = *Pass;
    sock = sock_;
    status = status_;

}

User::~User()
{
    
    
}

User::Notify_all()
{
    
    for ( auto it = Friends->begin (); it != Friends->end (); ++it ) {
        //Написать, ответ в форме isOnline
        std::string newMsg* = new std::string(""); 
        it->write_some(boost::asio::buffer(*newMsg));
        delete newMsg;
    }
    
}