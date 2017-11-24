#include <send.h>

bool send_ ( std::string* msg, std::string login, user_map_ptr smp )
{
    int bytes = 0;
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        if ( it->getLogin () == login ) {
            std::cout << login << std::endl;
            bytes = ( it->getSock () )->write_some ( boost::asio::buffer ( *msg ) );
        }
    }
    return bytes == sizeof ( *msg );
}