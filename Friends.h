#include <types.h>
#include <set>


class Friends{
    std::string User;
    std::set<std::string> FriendsSet;
    
public:
    Friends(std::string login){ User = login};
    ~Friends(){};
    
    static bool isOnline(const std::string* login);
    std::string getUser();
    std::set<std::string>* getFriends();
    addFriend(const std::string* login);
}