/**
		@file
		@brief Заголовочный файл с описанием класса, обрабатывающего сообщения
		
		Данный заголовочный файл содержит описание класса,
		реализующего обработку сообщений и вызова соответствующих функций
*/
#ifndef RECEIVER_H
#define RECEIVER_H
#include <acts.h>
#include <get_token.h>
#include <shared_queue.h>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

/**
		@brief Класс реализующий обработку сообщений
		
		Данный класс реализует обработку сообщений из очереди сообщений
		и вызывает соответствующие функции
		
		@author Delisa
*/

class receiver
{
   public:
    receiver () {}
    ~receiver () {}
/**
		@brief Функция-член, реализующая цикл чтения, обработки и ответа на сообщения
		
		Данная функция читает сообщения из очереди сообщений, обрабатывает их
		и генерирует соответствующий ответ
		@param[in] messageQueue очередь сообщений
		@param[in,out] smp Пул пользователей
		@param[in,out] ptree_ Дерево зарегистрированных пользователей
		
		@author Delisa
*/
    static void loop (MSG_queue_ptr messageQueue,
                      user_map_ptr smp,
                      ptree_ptr ptree_);
};

#endif  // RECEIVER_H
