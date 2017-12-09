#include <server.h>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <iostream>
#define DEFAULT_PORT 1488

void xgets (server* s_ptr)
{
    while (true) {
        std::cout << "Enter: ";
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
/*    boost::program_options::options_description opt_desc ("All options");
    opt_desc.add_options () 
        ("port",
        boost::program_options::value<int> ()->default_value (DEFAULT_PORT),
        "Set up server port") ("help", "Produce help message");

    boost::program_options::variables_map vm;

    boost::program_options::store (
        boost::program_options::parse_command_line (argc, argv, opt_desc), vm);

    boost::program_options::notify (vm);

    if (vm.count ("help")) {
        std::cout << opt_desc << std::endl;
        return 1;
    }

    int port;
    if (vm.count ("port")) {
        port << vm["port"].as<int> ();
    }

#ifdef DEBUG
    std::cout << "Current port is " << vm["port"].as<int> () << std::endl;
#endif
*/
    int port = DEFAULT_PORT;
    server* serv = new server (port);
    boost::thread (boost::bind (xgets, serv));
    if (serv) {
        serv->run ();
    }
}
