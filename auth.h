#ifndef AUTH_H
#define AUTH_H
#include <types.h>
#include <user.h>
bool auth (msg_ptr log,
           msg_ptr pass,
           user_map_ptr smp,
           socket_ptr sock,
           ptree_ptr ptree_);
#endif