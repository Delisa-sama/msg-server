/**
		@file
		@brief Заголовочный файл с описанием класса синхронизированной очереди
		
		Данный заголовочный файл содержит описание класса,
		реализующего синхронизированную работу с очередью
*/
#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H
#include <types.h>
#include <mutex>
#include <queue>

/**
		@brief Класс реализующий синхронизированную очередью
		
		Данный класс реализует синхронизированную работу с очередью 
		
		@author Delisa
*/

class Shared_queue
{
   public:
    Shared_queue (){};
    ~Shared_queue (){};

/**
		@brief Функция-член, реализующая добавление элемента в конец очереди
		
		Данная функция добавляет элемент в конец очереди
		@param[in] msg Сообщение
		
		@author Delisa
*/
		
    void push (msg_ptr msg);

/**
		@brief Функция-член, реализующая изъятие первого элемента из очереди
		
		Данная функция возвращает копию первого элемента из очереди 
		и удаляет его из очереди
		
		@return Возвращает сообщение
		
		@author Delisa
*/

    msg_ptr pop ();
		
/**
		@brief Функция-член, реализующая проверку очереди на пустоту
		
		Данная функция возвращает true, если очередь пуста
		или false в ином случае
		
		@return возвращает true, если очередь пуста или false в ином случае
		
		@author Delisa
*/
		
    bool empty () { return data.empty (); };
   private:
    std::mutex mutex_;///< Мьютекс для синхронизации очереди
    std::queue<std::string> data;///< Очередь для хранения сообщений
};
typedef boost::shared_ptr<Shared_queue> MSG_queue_ptr; ///< Очередь сообщений
#endif  // SHARED_QUEUE_H
