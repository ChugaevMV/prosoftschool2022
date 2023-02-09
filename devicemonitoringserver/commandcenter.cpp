#include "commandcenter.h"
#include <vector>
#include <math.h>


void CommandCenter::SetSchedule(DeviceWorkSchedule &Schedule)
{

    if (m_Device_Map.find(Schedule.deviceId) == m_Device_Map.end())
        m_Device_Map.insert(std::make_pair(Schedule.deviceId,Schedule.schedule));
}

std::string CommandCenter::GetMessage(uint64_t& deviceId, std::string &Message_fromServer)
{
    uint8_t meterage_from_device = m_serialize.GetMeterage(Message_fromServer);

    uint64_t timeStamp_from_device = m_serialize.GetTimeStamp(Message_fromServer);

    std::string Message_toServer;


    if (m_Device_Map.find(deviceId) == m_Device_Map.end())
    {
        Message_toServer = m_serialize.serialize_Message("NoSchedule");
        return Message_toServer;
    }

    uint64_t expTimeStamp_from_schedule_max = m_Device_Map[deviceId].back().timeStamp;
    uint64_t expTimeStamp_from_schedule_min = m_Device_Map[deviceId].at(0).timeStamp;

    if ((timeStamp_from_device < expTimeStamp_from_schedule_min) || (timeStamp_from_device > expTimeStamp_from_schedule_max))
    {
        Message_toServer = m_serialize.serialize_Message("NoTimestamp");
        return Message_toServer;
    }

    if (timeStamp_from_device < m_Device_info[deviceId].expectedTimestamp)
    {
        Message_toServer = m_serialize.serialize_Message("Obsolete");
        return Message_toServer;
    }

    std::vector <Phase> schedule = m_Device_Map[deviceId];

    int buffer;

    for (int i = 0; i < schedule.size(); i++)
    {
        if (schedule[i].timeStamp == timeStamp_from_device)
        {
            buffer = i;
            break;
        }

    }

    double command_to_server = schedule.at(buffer).value - meterage_from_device;

    Message_toServer = m_serialize.serialize_Message(command_to_server);

    double MSE = m_Device_info[deviceId].MSE;
    double count = m_Device_info[deviceId].count_of_calculation;

    m_Device_info[deviceId].MSE = sqrt((pow(MSE, 2) * count + pow(command_to_server, 2))/(count + 1));

    m_Device_info[deviceId].expectedTimestamp = timeStamp_from_device;

    m_Device_info[deviceId].count_of_calculation++;

    return Message_toServer;
}


double CommandCenter::GetMSE(uint64_t deviceId)
{
    if (m_Device_info.find(deviceId) == m_Device_info.end())
        return 0;
    return m_Device_info[deviceId].MSE;
}
