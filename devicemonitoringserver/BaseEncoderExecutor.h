#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H

#include <string>


/*!
 * \brief Базовый шифровальщика.
 */
class BaseEncoderExecutor
{
public:
//    virtual ~BaseEncoderExecutor() = default;

    /*!
     * \brief Обработчик сообщения, которое нужно закодировать.
     */
    virtual std::string encode(std::string &message);

    /*!
     * \brief Обработчик сообщения, которое нужно раскодировать.
     */
    virtual std::string decode(std::string &message);

    /*!
     * \brief Возврат названия использованного алгоритма шифрования.
     */
    virtual std::string name_of_encode_algorithm();

};
#endif // BASEENCODEREXECUTOR_H
