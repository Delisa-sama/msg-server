#include <send.h>
#include <iostream>
bool send_ ( msg_ptr msg, msg_ptr login, user_map_ptr smp )
{
    int bytes = 0;
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        std::cout << ( it->get ()->getLogin () ) << std::endl;
        if ( ( ( it->get ()->getLogin () ) == ( *login ) ) &&
             ( it->get ()->getSock ()->is_open () ) ) {
            std::cout << ( *login ) << std::endl;
            bytes =
                ( it->get ()->getSock () )->write_some ( boost::asio::buffer ( ( *msg ) ) );
            std::cout <<"DEBUG!!!!!   "<< *msg << std::endl;
            return bytes == sizeof ( ( *msg ) );
        }
    }
    return false;
}