#include <getBlock.h>
#include <receiver.h>
#include <send.h>
#include <string.h>
#include <iostream>

//Константы для типов сообщений

bool receiver::logout ( std::string* log, user_map_ptr smp )
{
    //Сменить статус у соответствующего User на Offline и выполнить функцию Notify_all
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        if ( *( it->getLogin () ) == *log ) {
            it->setStatus ( Offline );
            it->Notify_all ();
        }
    }
}

// bool receiver::reg ( const char* log, const char* pass )
//{
//    //нужно где-то помещать пользователя в мультисэт пользователей,
//    //а тут он будет записываться в json
//    try {
//        UserList.get<std::string> ( log );
//    } catch ( boost::property_tree::ptree_bad_path ) {
//        UserList.put ( log, pass );
//        return true;
//    }
//    return false;
//}

bool receiver::isExist ( std::string* search_log, socket_ptr requester_User, user_map_ptr smp )
{
    try {
        std::string FindedUser = UserList.get<std::string> ( log );
        if ( search_log == FindedUser ) {
            //Добавить в таблицу отслеживаемых юзеров
            for ( auto it = smp->begin (); it != smp->end (); ++it ) {
                if ( i ( t->getLogin () ) == search_log ) {
                    std::cout << search_log << std::endl;
                    ( it->getFriends () ).insert ( requester_User );
                }
            }
            return true
        } else {
            return false
        };
    } catch ( boost::property_tree::ptree_bad_path ) {
        std::cerr << "Not Found" << std::endl;
        return false;
    }
}

void receiver::loop ( MSG_queue_ptr messageQueue, user_map_ptr smp )
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

                switch ( getBlock ( *msg, 2 )[0] ) {
                case '1':
                    result = send_ ( getBlock ( *msg, 4 ), getBlock ( *msg, 3 ), smp );
                    break;
                //                case '2':
                //                    //авторизация
                //                    result = auth ( getBlock ( *msg, 3 ), getBlock ( *msg, 4
                //                    ) );
                //                    break;
                case '2':
                    // isExist
                    result = isExist ( getBlock ( *msg, 3 ), , smp );
                    break;
                }
                //отправка результата
                std::string* newMsg = new std::string ( getBlock ( *msg, 1 ) + ":" );
                if ( result ) {
                    newMsg += "0";
                } else {
                    newMsg += "1";
                };
                send_ ( newMsg, getBlock ( *msg, 2 ), smp );
                delete newMsg;
            }
            delete msg;
        }
    }