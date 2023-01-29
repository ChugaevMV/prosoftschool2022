#include "MessageSerializer.h"

/*
#include "devicemonitoringserver.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <handlers/abstractnewconnectionhandler.h>
#include <server/abstractconnection.h>
#include <servermock/connectionservermock.h>
*/
#include <sstream>
#include <iostream>

//MessageSerialiser::MessageSerialiser(AbstractMessageHandler* Message) :
//    m_Message(Message)
/*
MessageSerialiser::MessageSerialiser()
{

}

MessageSerialiser::~MessageSerialiser()
{
    //delete m_Message;
}
*/
//std::string MessageSerialiser::do_serialize_Meterage_Message(const uint8_t &meterages, const uint64_t &timeStamp)
std::string MessageSerialiser::serialize_Message(const uint8_t &meterages, const uint64_t &timeStamp)
{
    std::string Type = {"Meterage"};
    std::ostringstream strm;

    double u_meterages = static_cast <double> (meterages);

    strm << Type << " " << u_meterages << " " << timeStamp;

    writtenMessage = strm.str();

    return writtenMessage;
}

std::string MessageSerialiser:: serialize_Message(const double &command)
{
    std::string Type = {"Command"};
    std::ostringstream strm;

    strm << Type << " " << command;

    writtenMessage = strm.str();

    return writtenMessage;
}

std::string MessageSerialiser::serialize_Message(const std::string &type_error)
{
    std::string Type = {"Error"};
    std::ostringstream strm;

    strm << Type << " " << type_error;

    writtenMessage = strm.str();

    return writtenMessage;
}

std::string MessageSerialiser::GetTypeMessage(const std::string &message)
{
    std::istringstream strm_out(message);
    std::string Type_Message;
    strm_out >> Type_Message;

    return Type_Message;
}

uint8_t MessageSerialiser::GetMeterage(const std::string &message)
{
    std::istringstream strm_out(message);
    std::string Type_Message;
    uint64_t Time;
    uint8_t Meterage;
    strm_out >> Type_Message >> Meterage >> Time;

    return Meterage;
}

uint64_t MessageSerialiser::GetTimeStamp(const std::string &message)
{
    std::istringstream strm_out(message);
    std::string Type_Message;
    uint64_t Time;
    uint8_t Meterage;
    strm_out >> Type_Message >> Meterage >> Time;

    return Time;
}

std::string MessageSerialiser::GetTypeError(const std::string &message)
{
    std::istringstream strm_out(message);
    std::string Type_Message;
    std::string Type_error;
    strm_out >> Type_Message >> Type_error;

    return Type_error;
}

double MessageSerialiser::GetCommand(const std::string &message)
{
    std::istringstream strm_out(message);
    std::string Type_Message;
    double Command;
    strm_out >> Type_Message >> Command;

    return Command;
}

void MessageSerialiser:: deserialize_Message(const std::string &message)
{
    std::istringstream strm_out(message), strm_out1(message);
    std::string Type_Message;

    strm_out >> Type_Message;

    if (Type_Message == "Meterage")
    {
        uint64_t Time;
        uint8_t Meterage;
        strm_out1 >> Type_Message >> Meterage >> Time;

        std::cout << "This is " << Type_Message << " " << Meterage << " " << Time << std::endl;
    }
    if (Type_Message == "Command")
    {
        double Command;
        strm_out1 >> Type_Message >> Command;

        std::cout << "This is Command" << std::endl;
    }
    if (Type_Message == "Error")
    {
        std::string Type_error;
        strm_out1 >> Type_Message >> Type_error;

        std::cout << "This is Error" << std::endl;
    }

}
