#include <getBlock.h>
#include <receiver.h>
#include <string.h>
#include <iostream>

bool auth ( const char* log, const char* pass )
{
    // read json file
    if ( ( strcmp ( log, "admin1" ) ) && ( strcmp ( pass, "admin" ) ) ) {
        return true;
    } else {
        return false;
    }
}

int send_ ( std::string* msg, socket_ptr sock )
{
    return sock->write_some ( boost::asio::buffer ( *msg ) );
}

void receiver::loop ( MSG_queue_ptr messageQueue, socket_map_ptr smp )
{
    // boost::thread_group threads;
    std::cout << "LOOPED" << std::endl;
    while ( true ) {
        std::string* msg = ( new std::string ( "" ) );
        if ( !messageQueue->empty () ) {
            messageQueue->pop ( msg );
            if ( ( *msg != "" ) && ( msg != NULL ) ) {
                std::cout << *msg << std::endl;

                std::string login = getBlock ( *msg, 3 );

                for ( auto it = smp->begin (); it != smp->end (); ++it ) {
                    if ( it->first == login ) {
                        std::cout << login << std::endl;
                        send_ ( msg, it->second );
                    }
                }
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