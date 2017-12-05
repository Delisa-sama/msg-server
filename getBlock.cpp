#include <getBlock.h>
#include <boost/thread.hpp>
#include <iostream>
msg_ptr getBlock ( msg_ptr msg, int num )
{
    std::string tmpMsg ( *msg );

    std::cout << "DEBUG     getBlock       " << num << tmpMsg << std::endl;
    std::string tmp ( "" );
    int count = 1;
    for ( int i = 0;; i++ ) {
        if ( tmpMsg[i] == ':' ) {
            count++;
        } else if ( ( count > num ) || ( tmpMsg[i] == '\0' ) ) {
            break;
        } else if ( count == num ) {
            tmp += tmpMsg[i];
        }
    }
    std::cout << tmp << std::endl;
    msg_ptr tmp_ptr ( new std::string ( tmp ) );
    std::cout << "DEBUG     getBlock       " << ( *tmp_ptr ) << std::endl;
    return tmp_ptr;
}