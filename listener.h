/**
		@file
		@brief Заголовочный файл с описанием класса, слушающего порт
		
		Данный заголовочный файл содержит описание класса,
		реализующего прием новых соединений и прослушку текущих соединений
*/
#ifndef LISTENER_H
#define LISTENER_H
#include <acts.h>
#include <get_token.h>
#include <shared_queue.h>
#include <boost/asio.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>
#include <system_error>

/**
		@brief Класс реализующий прием данных от пользователей
		
		Данный класс реализует прием новых соединений и прослушку текущих соединений,
		а также прием данных и передачу их в очередь сообщений
		
		@author Delisa
*/

class listener
{
   public:
/**
		@brief Функция-член, реализующая прослушку текущего соединения
		
		Данная функция прослушивает соединение с определенным пользователем,
		принимает данные, составляет сообщение и передает в очередь соединений
		@param[in] sock Сокет, выделенный для данного пользователя
		@param[in,out] messageQueue очередь сообщений
		@param[in,out] smp Пул пользователей
		@param[in,out] ptree_ Дерево зарегистрированных пользователей
		
		@author Delisa
*/
    static void listen (socket_ptr sock,
                        MSG_queue_ptr messageQueue,
                        user_map_ptr smp,
                        ptree_ptr ptree_);
    listener () {}
    ~listener () {}
/**
		@brief Функция-член,  принимающая новые соединения
		
		Данная функция прослушивает данный ей порт,
		принимает новые соединения и передает управление данным соединением
		функции listen, выделяя ее в отдельный поток
		@param[in] service Средство ввода-вывода
		@param[in,out] q Очередь сообщений
		@param[in] port Порт для прослушки 
		@param[in,out] smp Пул пользователей
		@param[in,out] ptree_ Дерево зарегистрированных пользователей
		@param[in,out] flag Флаг, сигнализирующей об остановке сервера
		@param[in,out] listener_threads Пул для потоков, выделенных на пользователей
		
		@author Delisa
*/
    static void handle_connections (boost::asio::io_service* service,
                                    MSG_queue_ptr q,
                                    int port,
                                    user_map_ptr smp,
                                    ptree_ptr ptree_,
                                    bool* flag,
                                    boost::thread_group* listener_threads);
};
#endif  // LISTENER_H
