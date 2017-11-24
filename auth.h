#include <types.h>
bool auth ( std::string* log,
            std::string* pass,
            user_map_ptr smp,
            socket_ptr sock,
            boost::property_tree::ptree* ptree_ );