#ifndef MULTIPLY41_H
#define MULTIPLY41_H


#include "BaseEncoderExecutor.h"

class Multiply41 : BaseEncoderExecutor
{
public:

    /*!
     * \brief Обработчик сообщения, которое нужно закодировать.
     */
    std::string encode(std::string &message);

    /*!
     * \brief Обработчик сообщения, которое нужно раскодировать.
     */
    std::string decode(std::string &message);

    /*!
     * \brief Возврат названия использованного алгоритма шифрования.
     */
    std::string name_of_encode_algorithm();
};

#endif // MULTIPLY41_H
