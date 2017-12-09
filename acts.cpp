#include <acts.h>
#include <iostream>

bool auth (msg_ptr log,
           msg_ptr pass,
           user_map_ptr smp,
           socket_ptr sock,
           ptree_ptr ptree_)
{
    try {
        int count = 0;

        for (auto it = smp->begin (); it != smp->end (); ++it) {
            if ((((it->get ()->getLogin ()) == (*log)) &&
                 ((it->get ()->getPass ()) == (*pass))) ||
                ((ptree_->get<std::string> ((*log))) == (*pass))) {
                std::cout << "LOGGED: " << *log << std::endl;

                it->get ()->setStatus (types::Online);
                it->get ()->Notify_all ();

                return true;
            } else {
                count++;
            }
        }

        if ((count == smp->size ()) && (log->length () <= LOG_LEN) &&
            (pass->length () <= PASS_LEN)) {
            std::cout << "Creating new user: " << *log << std::endl;

            boost::shared_ptr<User> tmp (
                new User (log, pass, sock, types::Online));

            smp->push_back (tmp);

            try {
                ptree_->put (*log, *pass);
                boost::property_tree::write_json ("Users.json", *ptree_);

            } catch (boost::property_tree::ptree_bad_path) {
                std::cerr << "JSON Write error" << std::endl;

                return false;
            }
            return true;
        };
    } catch (...) {
        return false;
    }
    return false;
}

void logout (msg_ptr log, user_map_ptr smp)
{
    for (auto it = smp->begin (); it != smp->end (); ++it) {
        if ((it->get ()->getLogin ()) == *log) {
            it->get ()->getSock ()->close ();
            it->get ()->setStatus (types::Offline);
            it->get ()->Notify_all ();
        }
    }
}

bool send_ (msg_ptr msg, msg_ptr login, user_map_ptr smp)
{
    int bytes = 0;
    for (auto it = smp->begin (); it != smp->end (); ++it) {
        std::cout << (it->get ()->getLogin ()) << std::endl;
        if (((it->get ()->getLogin ()) == (*login)) &&
            (it->get ()->getSock ()->is_open ())) {
            std::cout << (*login) << std::endl;
            bytes = (it->get ()->getSock ())
                        ->write_some (boost::asio::buffer ((*msg)));
            std::cout << "Send msg to: " << *msg << std::endl;
            return bytes == sizeof ((*msg));
        }
    }
    return false;
}