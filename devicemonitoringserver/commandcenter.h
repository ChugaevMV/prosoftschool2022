#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <devicemock.h>
#include <MessageSerializer.h>
#include <deviceworkschedule.h>

#include <map>


struct Device{

    uint64_t expectedTimestamp = 0;

    double count_of_calculation = 0;

    double MSE;
};


class CommandCenter
{
public:
    /*!
     * \brief Реализация алгоритма выдачи решения от командного центра
     * \param Message_fromServer - сообщение, которое приходит от сервера
     * \param Message_toServer - сообщение, которое выдаёт командный центр (ошибка или команда)
     */
    std::string GetMessage (uint64_t& deviceId, std::string& Message_fromServer);

    /*!
     * \brief Реализация алгоритма задания плана работы устройства
     * \param deviceId - ID устройста для которого задаётся план работы
     * \param Schedule - план работу устройства, который необходимо задать для устройства
     */
    void SetSchedule (DeviceWorkSchedule& Schedule);

    /*!
     * \brief Реализация алгоритма возврата СКО (MSE)
     * \param deviceId - ID устройста для которого задаётся план работы
     */
    double GetMSE(uint64_t deviceId);

private:
    //uint64_t - ключ, ID устройства

    std::map <uint64_t, std::vector<Phase>> m_Device_Map;

    std::map <uint64_t, Device> m_Device_info;

    MessageSerialiser m_serialize;

};



#endif // COMMANDCENTER_H
