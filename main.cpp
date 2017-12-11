#include <server.h>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <iostream>
#define DEFAULT_PORT 1488 ///< Стандартный порт

void xgets (server* s_ptr)
{
    while (true) {
        char buff[256];
        std::cin.getline (buff, 256);
        std::string com (buff);
        if (com == "stop") {
            s_ptr->stop ();
            delete s_ptr;
            return;
        } else if (!s_ptr->get_flag ()) {
            return;
        }
    }
}

int main (int argc, char* argv[])
{
	
    int port = DEFAULT_PORT;
    server* serv = new server (port);
    boost::thread (boost::bind (xgets, serv));
    if (serv) {
        serv->run ();
    }
}
