#include <getBlock.h>
#include <receiver.h>
#include <send.h>
#include <string.h>
#include <iostream>

bool isExist ( std::string search_log,
               std::string requester_User,
               user_map_ptr smp,
               boost::property_tree::ptree* ptree_ )
{
    try {
        std::string FindedUser = ptree_->get<std::string> ( search_log );
        if ( FindedUser != "" ) {
            //Добавить в таблицу отслеживаемых юзеров
            bool flag = false;
            socket_ptr tmp;
            for ( auto it = smp->begin (); it != smp->end (); ++it ) {
                if ( ( !flag ) && ( *( it->get ()->getLogin () ) == requester_User ) ) {
                    tmp = it->get ()->getSock ();
                    flag = true;
                }
                if ( ( *( it->get ()->getLogin () ) == search_log ) && ( flag ) ) {
                    std::cout << search_log << std::endl;

                    ( it->get ()->getFriends () )->insert ( tmp );
                }
                return true;
            }
        }
    } catch ( boost::property_tree::ptree_bad_path ) {
        std::cerr << "Not Found" << std::endl;
        return false;
    }
}

void receiver::loop ( MSG_queue_ptr messageQueue,
                      user_map_ptr smp,
                      boost::property_tree::ptree* ptree_ )
{
    // code:typenum:login:text/pass/login

    // Каждый клиент запрашивает isExist, для каждого запрошенного юзера хранить список юзеров,
    // запросивших isExist на него
    // После isExist отправить статус о существовании пользователя и онлайн он или нет
    // При подключении/отключении юзера отправлять сообщение всем юзерам отслеживающим данного
    // boost::thread_group threads;
    std::cout << "LOOPED" << std::endl;
    while ( true ) {
        std::string* msg = ( new std::string ( "" ) );
        if ( !messageQueue->empty () ) {
            messageQueue->pop ( msg );
            if ( ( *msg != "" ) && ( msg != NULL ) ) {
                bool result = false;

                switch ( getBlock ( msg, 2 )[0] ) {
                case '1':
                    result = send_ ( getBlock ( msg, 4 ), getBlock ( msg, 3 ), smp );
                    break;
                case '2':
                    // isExist
                    result = isExist ( getBlock ( msg, 3 ), getBlock ( msg, 4 ), smp, ptree_ );
                    break;
                }

                //отправка результата
                std::string* newMsg = new std::string ( getBlock ( msg, 1 ) + ":" );

                if ( result ) {
                    *newMsg += "0";
                } else {
                    *newMsg += "1";
                };
                send_ ( *newMsg, getBlock ( msg, 2 ), smp );
                delete newMsg;
            }
            delete msg;
        }
    }
}