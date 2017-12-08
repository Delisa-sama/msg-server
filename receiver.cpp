#include <get_block.h>
#include <receiver.h>
#include <send.h>
#include <string.h>
#include <iostream>

bool isExist (msg_ptr search_log,
              msg_ptr requester_User,
              user_map_ptr smp,
              ptree_ptr ptree_)
{
    try {
        std::string FindedUser = ptree_->get<std::string> (*search_log);
        if (FindedUser != "") {
            bool flag = false;
            socket_ptr tmp;
            for (auto it = smp->begin (); it != smp->end (); ++it) {
                if ((!flag) && ((it->get ()->getLogin ()) == *requester_User)) {
                    tmp = it->get ()->getSock ();
                    flag = true;
                }
                if (((it->get ()->getLogin ()) == *search_log) && (flag)) {

                    it->get ()->addFriend (tmp);

                    return true;
                }
            }
        }
    } catch (boost::property_tree::ptree_bad_path) {
        std::cerr << "Not Found" << std::endl;
        return false;
    }
}

void receiver::loop (MSG_queue_ptr messageQueue,
                     user_map_ptr smp,
                     ptree_ptr ptree_)
{
    boost::mutex _mutex;
    while (true) {
        if (!messageQueue->empty ()) {
            msg_ptr msg (new std::string (messageQueue->pop ().operator* ()));
            if ((msg != NULL) && ((*msg) != "")) {
                bool result = false;
                if (static_cast<int> ((*msg)[5]) == 16) {
                    msg_ptr msg_ (new std::string (msg->substr (
                        0,
                        msg->length () - (getBlock (msg, 5)->length ()) - 1)));
                    result = send_ (msg_, getBlock (msg, 5), smp);

                } else {
                    msg_ptr newMsg (
                        new std::string (*(getBlock (msg, 1)) + ":"));
                    if (static_cast<int> ((*msg)[5]) == 4) {
                        result = isExist (getBlock (msg, 3), getBlock (msg, 4),
                                          smp, ptree_);
                        (*newMsg) += '\4';
                    } else if (static_cast<int> ((*msg)[5]) == 1) {
                        result = true;
                        (*newMsg) += '\1';
                    }

                    if (result) {
                        (*newMsg) += ":0";
                    } else {
                        (*newMsg) += ":1";
                    }
                    send_ (newMsg, getBlock (msg, 3), smp);
                }
            }
        }
    }
}