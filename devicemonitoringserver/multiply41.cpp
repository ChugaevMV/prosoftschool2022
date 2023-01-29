#include "multiply41.h"
#include <iostream>

#include <algorithm>

#include <sstream>

std::string Multiply41::encode(std::string &message)
{
    std::string encMessage;
    std::ostringstream stream;

    for (int i = 0; i < message.length(); i++)
    {
       double a = static_cast <double> (message[i]);

       a = a*41;
       stream << a << " ";

       encMessage = stream.str();
    }

    return encMessage;
}

std::string Multiply41::decode(std::string &message)
{
    std::string decMessage;
    int k = 0;
    int flag = 0;

    flag = std::count(message.begin(),message.end(), ' ');

    for (int i = 0; i < flag; i++)
    {
        std::string buffer = message.substr(k, 4);
        k += 5;

        double a = stod(buffer);

        a = a/41;

        char b = static_cast <char> (a);

        decMessage = decMessage+b;
    }

    return decMessage;
}

std::string Multiply41::name_of_encode_algorithm()
{
    return "Multiply41";
}
