#include <get_token.h>
#include <iostream>
msg_ptr get_token (msg_ptr msg, int num)
{
    std::string tmpMsg (*msg);
    std::string tmp ("");
    int count = 1;

    for (int i = 0;; ++i) {
        if (tmpMsg[i] == ':') {
            ++count;
        } else if ((count > num) || (tmpMsg[i] == '\0')) {
            break;
        } else if (count == num) {
            tmp += tmpMsg[i];
        }
    }

    msg_ptr tmp_ptr (new std::string (tmp));
    return tmp_ptr;
}
