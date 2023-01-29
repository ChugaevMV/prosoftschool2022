#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include <BaseEncoderExecutor.h>
#include <ro3.h>
#include <mirror.h>
#include <multiply41.h>

#include "stdint.h"
#include <string>
#include <iostream>

class MessageEncoder
{
public:

    /*!
     * \brief Реализация алгоритма шифрования в зависимости от типа
     * \param message - сообщение, которое необходимо зашифровать
     */
    std::string encode(std::string &message);


    /*!
     * \brief Реализация алгоритма расшифровки в зависимости от типа
     * \param message - сообщение, которое необходимо раскодировать
     */
    std::string decode (std::string &message);


    /*!
     * \brief Реализация алгоритма регистрации произвольного алгоритма шифрования
     * \param NewEncodeAlgoritm - указатель на наследника BaseEncoderAlgoritm (произвольного алгоритма)
     */
    void registration_algorithm (BaseEncoderExecutor* NewEncodeAlgoritm);


    /*!
    * \brief Выбор алгоритма шифрования/расшифрования.
    * \param nameofalgoritm - указание имени выбираемого алгоритма шифрования
    */
    void choice_algoithm(std::string &nameofalgoritm);



private:
    //uint32_t v_typeofalgorithm = 0;
    BaseEncoderExecutor* v_NewEncodeAlgoritm = nullptr;

};

#endif // MESSAGEENCODER_H
