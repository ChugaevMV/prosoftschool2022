#include "messageencoder.h"


std::string MessageEncoder::encode(std::string &message)
{
    return v_NewEncodeAlgoritm->encode(message);
}

std::string MessageEncoder::decode(std::string &message)
{
    return v_NewEncodeAlgoritm->decode(message);
}

void MessageEncoder::registration_algorithm(BaseEncoderExecutor* NewEncodeAlgoritm)
{
    v_NewEncodeAlgoritm = NewEncodeAlgoritm;
}

void MessageEncoder::choice_algoithm(std::string &message)
{
    if(message == "Multiply41")
    {
        //if(v_NewEncodeAlgoritm != nullptr) delete v_NewEncodeAlgoritm;

        //Multiply41* multiply = new Multiply41;
        Multiply41 multiply;
        v_NewEncodeAlgoritm = reinterpret_cast <BaseEncoderExecutor*> (&multiply);

    }

    if(message == "RO3")
    {
        //if(v_NewEncodeAlgoritm != nullptr) delete v_NewEncodeAlgoritm;

        //RO3* ro3 = new RO3;
        RO3 ro3;
        v_NewEncodeAlgoritm = reinterpret_cast <BaseEncoderExecutor*> (&ro3);
    }

    if(message == "Mirror")
    {
        //if(v_NewEncodeAlgoritm != nullptr) delete v_NewEncodeAlgoritm;

        //Mirror* mirror = new Mirror;
        Mirror mirror;
        v_NewEncodeAlgoritm = reinterpret_cast <BaseEncoderExecutor*> (&mirror);
    }
}





