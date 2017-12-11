#include <server.h>
#include <iostream>
void server::run ()
{
    try {
        boost::thread_group threads;
        boost::asio::io_service service;
        MSG_queue_ptr q (new Shared_queue ());
        ptree_ptr ptree_ (new boost::property_tree::ptree);

        try {
            boost::property_tree::read_json ("Users.json", *ptree_);
            ptree_->put ("admin", "admin");
        } catch (...) {
            ptree_->clear ();
        };

        boost::thread_group* listener_threads = new boost::thread_group ();

        threads.create_thread (boost::bind (listener::handle_connections,
                                            &service, q, port, smp, ptree_,
                                            &flag, listener_threads));
        threads.create_thread (boost::bind (receiver::loop, q, smp, ptree_));

        while (flag) {
        };

        listener_threads->interrupt_all ();
        threads.interrupt_all ();

        delete listener_threads;
    } catch (std::exception& e) {
        std::cerr << e.what () << std::endl;
    }
}

void server::stop ()
{
#ifdef DEBUG
    std::cout << "Stopping server" << std::endl;
#endif
    boost::system::error_code errCode;
    for (auto it = smp->begin (); it != smp->end (); ++it) {
        it->get ()->getSock ()->shutdown (
            boost::asio::ip::tcp::socket::shutdown_both, errCode);
        it->get ()->getSock ()->close ();
    }
    flag = false;
}
