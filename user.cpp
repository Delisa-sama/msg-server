#include <user.h>

User::User (msg_ptr Log,
            msg_ptr Pass,
            socket_ptr sock_,
            types::Status status_)
{
    Login = *Log;
    Password = *Pass;
    sock = sock_;
    status = status_;
    Friends = new std::set<socket_ptr>;
}

User::~User () { delete Friends; }
void User::Notify_all ()
{
    for (auto it = Friends->begin (); it != Friends->end (); ++it) {
        char tmp = static_cast<char> (status);

        std::string* newMsg = new std::string (Login + ":" + tmp, MSG_LEN);

        it->get ()->write_some (boost::asio::buffer (*newMsg));

        delete newMsg;
    }
}
