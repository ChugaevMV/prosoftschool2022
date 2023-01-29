#include "messageencoder.h"


std::string MessageEncoder::encode(std::string &message)
{
    return v_NewEncodeAlgoritm->encode(message);
}

//std::string MessageEncoder::encode(std::string &message, BaseEncoderExecutor* NewEncodeAlgoritm)
//{
//    return NewEncodeAlgoritm->encode(message);
//}

std::string MessageEncoder::decode(std::string &message)
{
    return v_NewEncodeAlgoritm->decode(message);
}


//std::string MessageEncoder::decode(std::string &message,BaseEncoderExecutor* NewEncodeAlgoritm)
//{
//    return NewEncodeAlgoritm->decode(message);
//}


void MessageEncoder::registration_algorithm(BaseEncoderExecutor* NewEncodeAlgoritm)
{
    v_NewEncodeAlgoritm = NewEncodeAlgoritm;
}


void MessageEncoder::choice_algoithm(std::string &message)
{
    if(message == "Multiply41")
    {
        Multiply41 multiply;
        v_NewEncodeAlgoritm = reinterpret_cast <BaseEncoderExecutor*> (&multiply);
    }

    if(message == "RO3")
    {
        RO3 ro3;
        v_NewEncodeAlgoritm = reinterpret_cast <BaseEncoderExecutor*> (&ro3);
    }

    if(message == "Mirror")
    {
        Mirror mirror;
        v_NewEncodeAlgoritm = reinterpret_cast <BaseEncoderExecutor*> (&mirror);
    }
}





