#include <getBlock.h>
#include <receiver.h>
#include <string.h>
#include <iostream>

//Константы для типов сообщений

bool logout(const char* log, user_map_prt smp)
{
    
    //Сменить статус на false
    
}

bool auth ( const char* log, const char* pass )
{
    // read json file
    try {
        std::string FindedPass = UserList.get<std::string> ( log );
        if ( pass == FindedPass ) {
            return true
        } else {
            return false
        };
    } catch ( boost::property_tree::ptree_bad_path ) {
        std::cerr << "Not Found" << std::endl;
        return false;
    }
}

bool isExist ( const char* search_log, const char* requeset_log )
{
    try {
        std::string FindedUser = UserList.get<std::string> ( log );
        if ( search_log == FindedUser ) {
            //Добавить в таблицу отслеживаемых юзеров
            
            mul.insert(std::pair<FindedUser, std::map<std::string>>);
            return true
        } else {
            return false
        };
    } catch ( boost::property_tree::ptree_bad_path ) {
        std::cerr << "Not Found" << std::endl;
        return false;
    }
}

bool send_ ( std::string* msg, std::string login, user_map_ptr smp )
{
    //    std::string login = getBlock ( *msg, 3 );
    int bytes = 0;
    for ( auto it = smp->begin (); it != smp->end (); ++it ) {
        if ( it->first == login ) {
            std::cout << login << std::endl;
            //            send_ ( msg, it->second );
            bytes = it->second->write_some ( boost::asio::buffer ( *msg ) );
        }
    }
    //    return sock->write_some ( boost::asio::buffer ( *msg ) );
    return bytes == sizeof ( *msg );
}

void receiver::loop ( MSG_queue_ptr messageQueue, user_map_ptr smp )
{
    // code:typenum:login:text/pass/login
    // 1:MSG; 2:login; 5:isExist

    // Каждый клиент запрашивает isExist, для каждого запрошенного юзера хранить список юзеров,
    // запросивших isExist на него
    // После isExist отправить статус о существовании пользователя и онлайн он или нет
    // При подключении/отключении юзера отправлять сообщение всем юзерам отслеживающим данного
    // boost::thread_group threads;
    std::cout << "LOOPED123" << std::endl;
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
                case '2':
                    //авторизация
                    result = auth ( getBlock ( *msg, 3 ), getBlock ( *msg, 4 ) );
                    break;
                case '5':
                    // isExist
                    result = isExist ( getBlock ( *msg, 3 ) );
                    break;
                }
                std::string newMsg ( getBlock ( *msg, 1 ) + ":" );
                if ( result ) {
                    newMsg += "0";
                } else {
                    newMsg += "1";
                };
                send_ ( &newMsg, getBlock ( *msg, 2 ), smp );
            }
        }

        // check queue
        /*if ( !messageQueue->empty () ) {
            messageQueue->pop ( msg );
        }

        if ( ( *msg != "" ) && ( msg != NULL ) ) {
            std::cout << *msg << std::endl;
            // msg
            if ( *msg[4] == "1" ) {
                // RECIEVE
                threads.create_thread (
                    boost::bind ( sender::send, getBlock(*msg, 2), getBlock(*msg, 4) , smp ) );
            }
            // login
            else if ( *msg[4] == "2" ) {
                if (auth(getBlock(*msg,2), getBlock(*msg,4)))
                {
                    threads.create_thread (
                    boost::bind ( sender::send, getBlock(*msg, 2), "0" , smp ) );
                } else {

                    threads.create_thread (
                    boost::bind ( sender::send, getBlock(*msg, 2), "1" , smp ) );
                };

            }
            // Register
            else if ( *msg[4] == "3" ) {
            }
            // isOnline
            else if ( *msg[4] == "4" ) {
            }
            // isExist
            else if ( *msg[4] == "5" ) {
            }
        };*/
        // delete msg;
    }
    // threads.join_all ();
}