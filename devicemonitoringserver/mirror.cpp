#include "mirror.h"
#include <algorithm>

std::string Mirror::encode(std::string &message)
{
    std::string encMessage = message;

    reverse(encMessage.begin(),encMessage.end());

    return encMessage;
}

std::string Mirror::decode(std::string &message)
{
    std::string decMessage = message;

    reverse(decMessage.begin(),decMessage.end());

    return decMessage;
}

std::string Mirror::name_of_encode_algorithm()
{
    return "Mirror";
}
