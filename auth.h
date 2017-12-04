#include <User.h>
#include <types.h>
#include <string.h>
bool auth ( std::string log,
            std::string pass,
            user_map_ptr smp,
            socket_ptr sock,
            ptree_ptr ptree_ );