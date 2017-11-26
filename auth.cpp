#include <auth.h>
#include <iostream>
bool auth ( std::string log,
            std::string pass,
            user_map_ptr smp,
            socket_ptr sock,
            boost::property_tree::ptree* ptree_ )
{
    //авторизация должна проходить первым сообщением
    int count = 0;
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        if ( ( *( it->get ()->getLogin () ) == log ) &&
             ( *( it->get ()->getPass () ) == pass ) ) {
            it->get ()->setStatus ( Online );
            it->get ()->Notify_all ();
            return true;
        } else {
            count++;
        }
    }
    if ( count == smp->size () ) {
        boost::shared_ptr<User> tmp ( new User ( &log, &pass, sock, Online ) );
        smp->push_back ( tmp );
        try {
            ptree_->add ( log, pass );
            boost::property_tree::write_json ( "Users.json", *ptree_ );
        } catch ( boost::property_tree::ptree_bad_path ) {
            std::cerr << "JSON Write error" << std::endl;
            return false;
        }
        return true;
    };
    return false;
}