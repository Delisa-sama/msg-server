#include <receiver.h>

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

                if (static_cast<int> ((*msg)[MSG_TYPE_POS]) == types::msg) {
                    msg_ptr msg_ (new std::string (msg->substr (
                        0, msg->length () -
                               (get_token (msg, types::Sender)->length ()) -
                               1)));

                    result = send_ (msg_, get_token (msg, types::Sender), smp);

                } else {
                    msg_ptr newMsg (
                        new std::string (*(get_token (msg, types::ID)) + ":"));

                    if (static_cast<int> ((*msg)[MSG_TYPE_POS]) == types::iex) {
                        result =
                            isExist (get_token (msg, types::Login),
                                     get_token (msg, types::Data), smp, ptree_);
                        (*newMsg) += static_cast<char> (types::iex);

                    } else if (static_cast<int> ((*msg)[MSG_TYPE_POS]) ==
                               types::log) {
                        result = true;
                        (*newMsg) += static_cast<char> (types::log);
                    }

                    if (result) {
                        (*newMsg) += ":0";
                    } else {
                        (*newMsg) += ":1";
                    }

                    send_ (newMsg, get_token (msg, types::Login), smp);
                }
            }
        }
    }
}
