#ifndef ACTS_H
#define ACTS_H
#include <types.h>
#include <user.h>
bool auth (msg_ptr log,
           msg_ptr pass,
           user_map_ptr smp,
           socket_ptr sock,
           ptree_ptr ptree_);
           
void logout (msg_ptr log, user_map_ptr smp);

bool send_ (msg_ptr msg, msg_ptr login, user_map_ptr smp);
#endif  // ACTS_H
