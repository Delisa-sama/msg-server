#include <Friends.h>

Friends::addFriend(const std::string* login)
{
    
    FriendsSet.insert(*login);
    
}

std::string Friends::getUser()
{
    
    return User;
    
}

std::set<std::string>* Friends::getFriends()
{
    
    return &FriendsSet;

}

bool Friends::isOnline(const std::string* login);