#ifndef DEVICEMONITORINGSERVER_H
#define DEVICEMONITORINGSERVER_H

#include "common.h"

#include <cstdint>
#include <string>

#include "MessageSerializer.h"
#include "messageencoder.h"

#include "commandcenter.h"

struct DeviceWorkSchedule;
class AbstractConnectionServer;
class AbstractConnection;

/*!
 * \brief Класс сервера для мониторинга состояния устройств.
 */
class DeviceMonitoringServer
{
    NON_COPYABLE(DeviceMonitoringServer)
public:
    /*!
     * \brief Конструктор.
     * \param connectionServer - владеющий указатель на сервер для приема подключений
     */
    DeviceMonitoringServer(AbstractConnectionServer* connectionServer);
    ~DeviceMonitoringServer();

    /*!
     * \brief Установить план работы устройств.
     */
    void setDeviceWorkSchedule(const DeviceWorkSchedule& Schedule);
    /*!
     * \brief Начать прием подключений по идентификатору \a serverId
     */
    bool listen(uint64_t serverId);

    void setEncodingAlgoritm(BaseEncoderExecutor* EncodeAlgoritm);

private:
    /*!
     * \brief Отправить сообщение устройству.
     * \param deviceId - идентификатор устройства
     * \param message - сообщение
     */
    void sendMessage(uint64_t deviceId, const std::string& message);
    /*!
     * \brief Обработчик приема нового сообщения от устройства.
     * \param deviceId - идентификатор устройства
     * \param message - сообщение
     */
    void onMessageReceived(uint64_t deviceId, const std::string& message);
    /*!
     * \brief Обработчик поступления нового входящего подключения.
     * \param conn - невладеющий указатель на объект подключения
     */
    void onNewIncomingConnection(AbstractConnection* conn);
    /*!
     * \brief Обработчик разрыва соединения.
     * \param deviceId - идентификатор устройства
     */
    void onDisconnected(uint64_t clientId);



private:
    void addMessageHandler(AbstractConnection* conn);
    void addDisconnectedHandler(AbstractConnection* conn);

private:
    AbstractConnectionServer* m_connectionServer = nullptr;

    uint64_t m_this_deviceId = 0;

    MessageSerialiser* m_serial = nullptr;
    MessageEncoder* m_encoder = nullptr;
    CommandCenter* m_commandcenter = nullptr;
};

#endif // DEVICEMONITORINGSERVER_H
