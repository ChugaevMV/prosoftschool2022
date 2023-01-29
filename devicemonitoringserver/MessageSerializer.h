#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include "common.h"

#include <string>
#include <vector>

//class AbstractMessageHandler;

/*!
 * \brief Класс, создающий сообщения
 */
class MessageSerialiser
{
//    NON_COPYABLE(MessageSerialiser)
public:
    /*!
     * \brief Конструктор.
     * \param Message - владеющий указатель на объект класса сериализатора сообщения
     */
//    MessageSerialiser(AbstractMessageHandler* Message);
//    MessageSerialiser() = default;
//    ~MessageSerialiser();


public:
    /*!
     * \brief Создать сообщение со значением переменной
     */
    //std::string do_serialize_Meterage_Message(const uint8_t &meterages, const uint64_t &timeStamp);

    std::string serialize_Message(const uint8_t &meterages, const uint64_t &timeStamp);

    /*!
     * \brief Создать командное сообщение
     */
    //void do_serialize_Command_Message(double command);
    std::string serialize_Message(const double &command);


    /*!
     * \brief Создать сообщение об ошибке
     */
    //void do_serialize_Error_Message(std::string& message);
    std::string serialize_Message(const std::string &type_error);


    /*!
     * \brief Распарсить сообщение
     */
    //void do_deserialize_Message(const std::string& message);
    void deserialize_Message(const std::string &message);

    /*!
     * \brief Вернуть тип передаваемого сообщения (строка)
     */
    std::string GetTypeMessage(const std::string &message);

    /*!
     * \brief Вернуть значение измерения
     */
    uint8_t GetMeterage(const std::string &message);

    /*!
     * \brief Вернуть метку времени
     */
    uint64_t GetTimeStamp(const std::string &message);

    /*!
     * \brief Вернуть тип ошибки
     */
    std::string GetTypeError(const std::string &message);

    /*!
     * \brief Вернуть значение команды
     */
    double GetCommand(const std::string &message);

private:
//    AbstractMessageHandler* m_Message = nullptr;
    std::string writtenMessage;
    //std::string s_Type;
    //uint64_t s_Time;
    //uint8_t s_Meterage;
    //std::string s_Type_error;
};


#endif // MESSAGESERIALIZER_H
