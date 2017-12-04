#include <getBlock.h>
#include <receiver.h>
#include <send.h>
#include <string.h>
#include <iostream>

bool isExist ( std::string* search_log,
               std::string* requester_User,
               user_map_ptr smp,
               ptree_ptr ptree_ )
{
    try {
        std::string FindedUser = ptree_->get<std::string> ( *search_log );
        if ( FindedUser != "" ) {
            //Добавить в таблицу отслеживаемых юзеров
            bool flag = false;
            socket_ptr tmp;
            for ( auto it = smp->begin (); it != smp->end (); ++it ) {
                if ( ( !flag ) && ( *( it->get ()->getLogin () ) == *requester_User ) ) {
                    tmp = it->get ()->getSock ();
                    flag = true;
                }
                if ( ( *( it->get ()->getLogin () ) == *search_log ) && ( flag ) ) {
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
        if ( ( messageQueue->is_lock_free () ) && ( !messageQueue->empty () ) ) {
            std::string* msg;
            while ( !(_mutex.try_lock () )) {
            };
            messageQueue->pop ( msg );
            _mutex.unlock();
            //std::cout << *msg << std::endl;
            if ( ( msg != NULL ) && ( *msg != "" ) ) {
                bool result = false;
                if ( ( *msg )[5] == '\16' ) {
                    //std::cout << "send: " << *msg << "to" << *( getBlock ( msg, 3 ) )
                    //          << std::endl;
                    result = send_ ( *( getBlock ( msg, 4 ) ), *( getBlock ( msg, 3 ) ), smp );

                } else {
                    std::string* newMsg =
                        new std::string ( *( getBlock ( msg, 1 ) ) + ":", 256 );
                    if ( ( *msg )[5] == '\4' ) {
                        std::cout << "iEx" << std::endl;
                        result =
                            isExist ( getBlock ( msg, 3 ), getBlock ( msg, 4 ), smp, ptree_ );
                        *( newMsg ) += '\4';
                    } else if ( ( *msg )[5] == '\1' ) {
                        std::cout << "Auth!!!" << std::endl;
                        result = true;
                        *( newMsg ) += '\1';
                    }

                    if ( result ) {
                        *newMsg += ":0";
                    } else {
                        *newMsg += ":1";
                    };
                    //std::cout << *newMsg << std::endl;
                    send_ ( *newMsg, *( getBlock ( msg, 3 ) ), smp );
                    delete newMsg;
                }
                delete msg;
            }
        }
    }
}