#include "ro3.h"


std::string RO3::encode(std::string &message)
{
    const int ROT3 = 3;
        std::string encMessage = message;

        for (size_t i = 0; i < encMessage.size();i++)
        {
            encMessage[i] = encMessage[i] + ROT3;
        }

        return encMessage;
}

std::string RO3::decode(std::string &message)
{
        const int ROT3 = 3;
        std::string decMessage = message;

        for (size_t i = 0; i < decMessage.size();i++)
        {
            decMessage[i] = decMessage[i] - ROT3;
        }

        return decMessage;
}

std::string RO3::name_of_encode_algorithm()
{
        return "RO3";
}
