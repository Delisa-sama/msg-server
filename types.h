/**
		@file
		@brief Заголовочный файл с описанием основных типов, инклюдов,
		перечислимых типов и констант
		
		Данный заголовочный файл содержит описание основных типов, инклюдов,
		перечислимых типов и констант
*/
#ifndef TYPES_H
#define TYPES_H
#include <string.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <set>

#define MSG_LEN 256 ///< Максимальная длина сообщения
#define MSG_TYPE_POS 5 ///< Позиция бита типа сообщения
#define MSG_ID_LEN 4 ///< Длинная идентификатора сообщения

#define LOG_LEN 16 ///< Максимальная длина логина
#define PASS_LEN 16 ///< Максимальная длина пароля

typedef boost::shared_ptr<std::string> msg_ptr; ///< Сообщение
typedef boost::shared_ptr<boost::property_tree::ptree> ptree_ptr; ///< Дерево зарегистрированных пользователей
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr; ///< Сокет
namespace types
{
/// Возможные типы сообщений
enum msgType {

    log = 1, ///< Авторизоваться
    reg = 2, ///< Зарегистрироваться
    iex = 4, ///< Проверка на существование
    ion = 8, ///< Проверка на статус онлайн
    msg = 16 ///< Переслать сообщение

};
/// Возможные номера токенов
enum Tokens { 
		ID = 1, ///< Идентификатор сообщения
		Type = 2, ///< Тип сообщения
		Login = 3, ///< Логин
		Data = 4, ///< Данные(Пароль/текст сообщения)
		Sender = 5 ///< Логин отправителя
 };
/// Возможные статусы пользователей
enum Status { 
		Online = 0, ///< Пользователь в сети
		Offline, ///< Пользователь не в сети
		NotAuth ///< Пользователь еще не прошел аутентификацию
};
}

#endif  // TYPES_H
