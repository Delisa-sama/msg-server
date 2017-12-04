#include <getBlock.h>
std::string getBlock ( std::string* msg, int num )
{
    int count = 1;
    std::string* tmp = new std::string ( "", 256 );
    for ( int i = 0;; i++ ) {
        if ( (*msg)[i] == ':' ) {
            count++;
        } else if ( count == num ) {
            (*tmp) += (*msg)[i];
        } else if ( ( count > num ) || ( i == msg->length () ) ) {
            break;
        };
    }
    return *tmp;
}