/**
		@file
		@brief Заголовочный файл с описанием класса сервер
		
		Данный заголовочный файл содержит описание класса,
		реализующего запуск и остановку сервера
*/
#ifndef SERVER_H
#define SERVER_H
#include <listener.h>
#include <receiver.h>

/**
		@brief Класс реализующий управление сервером
		
		Данный класс реализует запуск и остановку сервера
		
		@author Delisa
*/

class server
{
   public:
    server (int port_)
    {
        smp.reset (new (std::list<boost::shared_ptr<User>>));
        port = port_;
        flag = true;
    };
    ~server (){};

    void run ();
    void stop ();
    bool get_flag () { return flag; };
   private:
    bool flag;
    int port;
    user_map_ptr smp;
};
#endif  // SERVER_H
