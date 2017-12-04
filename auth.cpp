#include <auth.h>
#include <iostream>
bool auth ( std::string log,
            std::string pass,
            user_map_ptr smp,
            socket_ptr sock,
            ptree_ptr ptree_ )
{
    try {
        int count = 0;
        for ( auto it = smp->begin (); it != smp->end (); ++it ) {
            if ( ( *( it->get ()->getLogin () ) == log ) &&
                 ( *( it->get ()->getPass () ) == pass ) &&
                 ( ( ptree_->get<std::string> ( log ) ) == pass ) ) {
                it->get ()->setStatus ( Online );
                it->get ()->Notify_all ();
                return true;
            } else {
                count++;
            }
        }
        if ( count == smp->size () ) {
            std::cout << "newUser" << std::endl;
            boost::shared_ptr<User> tmp ( new User ( log, pass, sock, Online ) );
            std::cout << ( *( tmp->getLogin () ) ) << std::endl;
            smp->push_back ( tmp );
            try {
                std::cout << "logpass  " << log << ":" << pass << std::endl;
                ptree_->put ( log, pass );
                boost::property_tree::write_json ( "Users.json", *ptree_ );
            } catch ( boost::property_tree::ptree_bad_path ) {
                std::cerr << "JSON Write error" << std::endl;
                return false;
            }
            return true;
        };
    } catch ( ... ) {
        return false;
    }
    return false;
}