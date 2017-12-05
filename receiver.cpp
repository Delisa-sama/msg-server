#include <getBlock.h>
#include <receiver.h>
#include <send.h>
#include <string.h>
#include <iostream>

bool isExist ( msg_ptr search_log, msg_ptr requester_User, user_map_ptr smp, ptree_ptr ptree_ )
{
    try {
        std::string FindedUser = ptree_->get<std::string> ( *search_log );
        if ( FindedUser != "" ) {
            //Добавить в таблицу отслеживаемых юзеров
            bool flag = false;
            socket_ptr tmp;
            for ( auto it = smp->begin (); it != smp->end (); ++it ) {
                if ( ( !flag ) && ( ( it->get ()->getLogin () ) == *requester_User ) ) {
                    tmp = it->get ()->getSock ();
                    flag = true;
                }
                if ( ( ( it->get ()->getLogin () ) == *search_log ) && ( flag ) ) {
                    std::cout << *search_log << std::endl;

                    it->get ()->addFriend ( tmp );

                    return true;
                }
            }
        }
    } catch ( boost::property_tree::ptree_bad_path ) {
        std::cerr << "Not Found" << std::endl;
        return false;
    }
}

void receiver::loop ( MSG_queue_ptr messageQueue, user_map_ptr smp, ptree_ptr ptree_ )
{
    boost::mutex _mutex;
    std::cout << "LOOPED" << std::endl;
    while ( true ) {
        if ( !messageQueue->empty () ) {
            msg_ptr msg ( new std::string ( messageQueue->pop ().operator* () ) );
            std::cout << "DEBUG     " << ( *msg ) << std::endl;
            if ( ( msg != NULL ) && ( ( *msg ) != "" ) ) {
                bool result = false;
                if ( ( (int)( *msg )[5] ) == 16 ) {
                    msg_ptr msg_ ( new std::string ( msg->substr (
                        0, msg->length () - ( getBlock ( msg, 5 )->length () ) - 1 ) ) );
                    std::cout << "DEBUG     " << ( *msg_ ) << std::endl;
                    result = send_ ( msg_, getBlock ( msg, 5 ), smp );

                } else {
                    msg_ptr newMsg ( new std::string ( *( getBlock ( msg, 1 ) ) + ":" ) );
                    if ( ( (int)( *msg )[5] ) == 4 ) {
                        std::cout << "iEx" << std::endl;
                        result =
                            isExist ( getBlock ( msg, 3 ), getBlock ( msg, 4 ), smp, ptree_ );
                        ( *newMsg ) += '\4';
                    } else if ( ( (int)( *msg )[5] ) == 1 ) {
                        std::cout << "DEBUG     "
                                  << "Auth!!!" << std::endl;
                        result = true;
                        ( *newMsg ) += '\1';
                    }

                    if ( result ) {
                        ( *newMsg ) += ":0";
                    } else {
                        ( *newMsg ) += ":1";
                    };
                    std::cout << "DEBUG     " << *newMsg << std::endl;
                    send_ ( newMsg, getBlock ( msg, 3 ), smp );
                }
            }
        }
    }
}