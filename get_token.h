/**
		@file
		@brief Заголовочный файл с описанием свободный функции полуыения токена
		
		Данный заголовочный файл содержит описание функции,
		реализующей возврат токена из сообщения по его номеру
*/
#ifndef GET_BLOCK_H
#define GET_BLOCK_H
#include <types.h>
#include <boost/thread.hpp>

/**
		@brief Свободная функция, реализующая возврат токена по номеру
		
		Данная функция проводит возврат токена по номеру
		@param[in] msg Сообщение
		@param[in] num Номер токена
		
		@return Возвращает токен по его номеру
		
		@author Delisa
*/

msg_ptr get_token (msg_ptr msg, int num);
#endif  // GET_BLOCK_H
